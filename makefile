CC=gcc
ARGS=-Wall -Wextra
karatsuba: karatsuba.c polynome.o
	$(CC) karatsuba.c polynome.o $(ARGS) -o karatsuba

polynome.o: polynome.h polynome.c
	$(CC) -c polynome.c $(ARGS) 

extendedEuclid.o: extendedEuclid.o
	$(CC) -c extendedEuclid.c $(ARGS)

montgomery: montgomery.c extendedEuclid.o
	$(CC) montgomery.c extendedEuclid.o $(ARGS) -o montgomery
