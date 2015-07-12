#include "crypt.h"
#include <stdio.h>

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

main()
{
    uint64_t gcd, a, b;
    long long int x, y;
    a = 7;
    b = 5;
    eea(a,b,&gcd,&x,&y);    
    printf("a: %lld b: %lld gcd: %lld x: %lld y: %lld",a,b,gcd,x,y);
}
