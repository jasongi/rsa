#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "./crypt.h"
#include "./rsa.h"

/*  
    Copyright (C) 2013 Jason Giancono (jasongiancono@gmail.com)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

/*max number of p and q*/
#define PMAX 10000
/*min number of p and q*/
#define PMIN 1000

/*  this program does three different things depending on the 
    flags given. -g will generate a public key e, private key d
    and a modulo n. -e will take in/out filenames, a key and n
    and it will encrypt the in file and save it to the out file.
    -d will take an in/out filename, a key and a n and it will
    decrypt the in file and save it to the out file. The reason
    I didn't have key generation and encryption happen at the same
    time is because with RSA, the person you're encrypting the message
    for is the person who generates the key to encrypt it with*/
int main(int argc, char** argv)
{
    /*  the usage will print if the arguments are wrong*/
	char usage[] = "rsa by Jason Giancono\nUSAGE: rsa <FLAG>\nFLAGS:\t\t-g: generate keys\n\t\t-d <input filename> <output filename> <key> <n modulo>: decrypt file using key and modulo and output to <output filename>\n\t\t-e <input filename> <output filename> <key> <n modulo>: encrypt file using key and modulo and output to <output filename>\n";
	/*  seed the PRNG when the program starts*/
    srand(time(NULL));
    /*  variable for i/o errors*/
    int error = 0;
    /*  test to see if the -g flag and make sure there is any arguments at all
        (it will segfault otherwise*/
    if ( (argc != 1) && !strcmp(argv[1],"-g") )
    {
        uint64_t pub, priv,n;
        /*generates the keys*/
        generateKeys(&pub, &priv, &n);
        /*print the keys to the terminal*/ 
        printf("\nKeys:\t\t\tPublic: \t%llu\n\t\t\tPrivate: \t%llu\n\t\t\tN: \t\t%llu\n", pub, priv, n);
    }
    else if (argc ==6)
    {
        uint64_t key,n;
        /*open files for reading/writing*/
        FILE *input,*output;
        input = fopen(argv[2], "r");
        output = fopen(argv[3], "w");
        /*convert arguments to integers*/
        key = strtoll(argv[4], NULL,10);
        n = strtoll(argv[5], NULL,10);
        /*calculate the amount of chars I can fit in one encryption block*/
        int arraySize = (msb(n)-1)/8;
        /*make sure the files opened OK*/
        if(output != NULL)
        {
            if(input !=NULL)
            {
                /*check the flag for encrypt*/
                if(!strcmp(argv[1], "-e"))
                {
                    /*continue reading and encrypting until an error or end of file*/
                    while((!feof(input)) && !ferror(input) && !ferror(output) )
                    {
                        /*make the array size 8 because then it is sizeof(uint64_t)*/
                        char block[8];
                        memset(block,0,8);
                        int ii;
                        /*read characters into the array*/
                        for(ii=0;ii<arraySize;ii++)
                        {
                                block[ii] = getc(input);
                        }
                        /*dirty pointer manipulation so you can do FMEA on the array*/
                        uint64_t *m = (uint64_t*)block;
                        /*do the RSA encryption*/
                        *m = fmea(*m,key,n);
                        /*  write characters into encrypted file, one extra character is copied
                            copies the arraySize+1 because the FMEA may have made the block
                            larger than it's original size*/
                        for(ii=0;ii<arraySize+1;ii++)
                        {
                            putc(block[ii],output);
                        }
                    }
                }
                /*check the flag for decrypt*/
                else if(!strcmp(argv[1], "-d"))
                {
                    /*continue reading and encrypting until an error or end of file*/
                    while((!feof(input)) && !ferror(input) && !ferror(output) )
                    {
                        /*make the array size 8 because then it is sizeof(uint64_t)*/
                        char block[8];
                        memset(block,0,8);
                        int ii;
                        /*read characters into the array*/
                        for(ii=0;ii<arraySize+1;ii++)
                        {
                                block[ii] = getc(input);
                        }
                        /*dirty pointer manipulation so you can do FMEA on the array*/
                        uint64_t *m = (uint64_t*)block;
                        /*do the RSA decryption*/
                        *m = fmea(*m,key,n);
                        /*  write characters into decrypted file, check for EOF so that
                        you don't copy in extra junk.*/
                        for(ii=0;ii<(arraySize);ii++)
                        {
                                if(!feof(input) && (block[ii] != EOF))
                                    putc(block[ii],output);
                        }
                    }
                }
                else error = 1;
            }
            else error = 1;
        }
        else error = 1;
        /*error handling*/
        if (error || ferror(output) || ferror(input))
        {
            error = 1;
            perror("An Error Occurred");
            if (output !=NULL)
                fclose(output);
            if (input != NULL)
                fclose(input);
        }
        else
        {
        /*close the files*/
        fclose(output);
        fclose(input);
        }
    }
    /*print the usage because the muffin obviously doesn't know the arguments*/
    else printf("Wrong number of args \n\n%s", usage);
    return error;  
}
/*  this function generates a public key, private key and modulo n
    for RSA encryption. srand needs to be seeded */
void generateKeys(uint64_t* pub, uint64_t* priv, uint64_t* n)
{
    uint64_t p,q,phiN;
    /*  generate a random p between given range
        until p passes the lehmann primality 
        test function*/
    do 
    {
        p = ( rand() % (PMAX-PMIN) ) + PMIN;
    }
    while(!lehmann(p));
    /*  generate a random q between given range
        until q passes the lehmann primality 
        test function*/
    do    
    {
        q = ( rand() % (PMAX-PMIN) ) + PMIN;
    }
    while(!lehmann(q));
    /*calulate the modulo n to pass back*/
    *n=p*q;
    /*calculate φ(n)*/
    phiN =(p-1)*(q-1);
    uint64_t e,gcd,d;
    long long int xi,yi;
    /*  calcuate e and test to see that it is co-prime with
        φ(n)*/
    do
    {
        e = rand()%(phiN-3)+2;
        eea(e,phiN,&gcd,&xi,&yi);
    }
    while(gcd !=1);
    /*  using the value fromt he EEA function, get your 
        private key d (need to had φ(n) and mod φ(n) to
        make sure it is positive*/
    d = (uint64_t)((xi+phiN)%phiN);
    /*pass back the public and private keys*/
    *pub = e;
    *priv = d;
}
