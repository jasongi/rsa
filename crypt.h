#include <stdint.h>
unsigned short permute(unsigned short input, int* permutation,int inputLen, int outputLen);
uint64_t powerOf2(unsigned short exponent);
void printBin(uint64_t bin, int bitNum, int* array);
uint64_t fmea(uint64_t a,uint64_t b,uint64_t n);
void eea(uint64_t a, uint64_t b, uint64_t* gcd, long long int*xi, long long int* yi);
int lehmann(uint64_t p);
int msb(uint64_t in);
