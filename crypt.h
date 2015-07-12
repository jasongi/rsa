#include <stdint.h>

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


unsigned short permute(unsigned short input, int* permutation,int inputLen, int outputLen);
uint64_t powerOf2(unsigned short exponent);
void printBin(uint64_t bin, int bitNum, int* array);
uint64_t fmea(uint64_t a,uint64_t b,uint64_t n);
void eea(uint64_t a, uint64_t b, uint64_t* gcd, long long int*xi, long long int* yi);
int lehmann(uint64_t p);
int msb(uint64_t in);
