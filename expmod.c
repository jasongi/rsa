#include <stdio.h>
#include "crypt.h"

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


