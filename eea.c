#include "crypt.h"
#include <stdio.h>
main()
{
    uint64_t gcd, a, b;
    long long int x, y;
    a = 7;
    b = 5;
    eea(a,b,&gcd,&x,&y);    
    printf("a: %lld b: %lld gcd: %lld x: %lld y: %lld",a,b,gcd,x,y);
}
