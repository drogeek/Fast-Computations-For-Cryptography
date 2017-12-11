CC=gcc
ARGS=-Wall -Wextra
karatsuba: karatsuba.c polynome.o
	$(CC) karatsuba.c polynome.o $(ARGS) -o karatsuba

polynome.o: polynome.h polynome.c
	$(CC) -c polynome.c $(ARGS) 
