all: rsa expmod eea
	
eea: eea.o crypt.o
	gcc -o eea eea.o crypt.o
eea.o: eea.c crypt.h
	gcc -c eea.c
rsa: rsa.o crypt.o
	gcc -o rsa rsa.o crypt.o
expmod: expmod.o crypt.o
	gcc -o expmod expmod.o crypt.o
crypt.o: crypt.c crypt.h
	gcc -c crypt.c
expmod.o: expmod.c crypt.h
	gcc -c expmod.c
rsa.o: rsa.c crypt.c
	gcc -c rsa.c
clean:
	rm *.o rsa expmod *~
