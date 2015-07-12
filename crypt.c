#include <stdio.h>
#include "crypt.h"
/*  TESTNUMBER is the amount of times the Lehmann algorithm runs per test*/
#define TESTNUMBER 50

/*  powerOf2 takes an integer and returns two to the power of that integer*/
uint64_t powerOf2(unsigned short exponent)
{
	int ii;
	uint64_t retVal = 1;
	for (ii=0;ii<exponent;ii++)
		retVal = retVal*2;
	return retVal;
}

/*  converts a 64 bit int into an array of ints, each element representing one bit*/
void binConvert(uint64_t bin, int bitNum, int* array)
{
	int ii;
	for(ii=(bitNum-1); ii>=0;ii--)
	{
		if( ( bin & powerOf2(ii) ) > 0)
			array[ii] = 1;
		else
			array[ii] = 0;
	}
}

/*  Fast Modular Exponentation Algorithm for a^b mod n*/
uint64_t fmea(uint64_t a,uint64_t b, uint64_t n)
{
    uint64_t f = 1;
    int b_binary[64];
    /*convert the integer into a binary array*/
    binConvert(b,64,b_binary);
    int ii = 63;
    while (ii >= 0)
    {
        f = (f * f) % n;
        if (b_binary[ii] == 1)
           f = (f * a) % n;
        ii--;
    }
    return f;
}

/*  extended Euclidean algorithm, solves ax+by = gcd(a,b) given a and b*/
void eea(uint64_t a, uint64_t b, uint64_t* gcd, long long int*xi, long long int* yi)
{
    long long int xiPlus1, yiPlus1, xiPlus2, yiPlus2, quotient, remainder;
    /*starting cases*/
    *xi = 0;
    *yi = 1;
    xiPlus1 = 1;
    yiPlus1 = 0;
    *gcd = b;
    while (a!=0)
    {
        quotient = *gcd/a;
        remainder = *gcd%a;
        xiPlus2 = *xi-xiPlus1*quotient;
        yiPlus2 = *yi-yiPlus1*quotient;
        *gcd = a;
        a = remainder;
        *xi = xiPlus1;
        *yi = yiPlus1;
        xiPlus1 = xiPlus2;
        yiPlus1 = yiPlus2;
    }
}

/*  make sure you've seeded srand() before calling this!*/
int lehmann(uint64_t p)
{
    int ii = 0;
    uint64_t x;
    /*we start off assuming the number is prime*/
    int probablyPrime = 1;
    while((probablyPrime) && (ii<TESTNUMBER))
    {
        x = fmea((rand()%p),(p-1)/2,p);
        /*if x isn't 1 or p-1, then we are sure p is not prime*/
        if(!( (x == 1) || (x == p-1) ))
            probablyPrime = 0;
        ii++;
        /*if x was 1 or p-1, then run the loop again until it reaches TESTNUMBER*/
    }
    return probablyPrime;
}
/*  Function for finding the most significant bit in a 64 bit integer
    It is used to figure out how many characters we can cram into an
    RSA encryption block for a certain modulo N*/
int msb(uint64_t in)
{
    int ii;
    int mostSig=1;
    for(ii=2;ii<65;ii++)
    {
        in = in>>1;
        if (in&1==1)
            mostSig = ii;
    }
    return mostSig;
}
