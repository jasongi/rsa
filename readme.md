#rsa

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

This was a task for an assignment in a cryptography unit in my undergraduate computer science degree. This was written in 2013. It is the implementation of basic RSA. The algorithm used is not cryptographically secure and should only be used when learning about RSA.

This program does three different things depending on the  flags given. 
-g will generate a public key e, private key d and a modulo n. 
-e will take in/out filenames, a key and n and it will encrypt the in file and save it to the out file. 
-d will take an in/out filename, a key and a n and it will decrypt the in file and save it to the out file. 


 USAGE: rsa <FLAG>
 FLAGS:     -g: generate keys
            
            -d <input filename> <output filename> <key> <n modulo>: decrypt file using key and modulo and output to <output filename>
            
            -e <input filename> <output filename> <key> <n modulo>: encrypt file using key and modulo and output to <output filename>
            
Also included is expmod, which computes a^b mod n for positive integer numbers a, b n with length less than 10 digits

rsa.sh goes through a test using a sample public/private key set.