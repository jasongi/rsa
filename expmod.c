#include <stdio.h>
#include "crypt.h"
/***************************************************************
This programtakes three integer arguments, a, b and n respectively where
    a is the base
    b is the exponent
    n is the modulo
****************************************************************/
int main(int argc, char** argv)
{
    long long int a,b,n;
    a = strtoll(argv[1], NULL,10);
    b = strtoll(argv[2], NULL,10);
    n = strtoll(argv[3], NULL,10);
    /*print the result of a^b mod n*/
    printf("\n------\n%lld\n------\n",fmea(a,b,n));
    return 0;  
}


