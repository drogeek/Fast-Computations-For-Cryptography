CC=gcc
ARGS=-Wall -Wextra -lgmp
all: karatsuba brauer squareMultiply
karatsuba: karatsuba.c polynome.o binaryOperation.o
	$(CC) karatsuba.c polynome.o binaryOperation.o $(ARGS) -o karatsuba

polynome.o: polynome.h polynome.c
	$(CC) -c polynome.c $(ARGS) 

extendedEuclid.o: extendedEuclid.c extendedEuclid.h
	$(CC) -c extendedEuclid.c $(ARGS)

binaryOperation.o: binaryOperation.h binaryOperation.c
	$(CC) -c binaryOperation.c $(ARGS)

montgomery.o: montgomery.c
	$(CC) -c montgomery.c $(ARGS)

brauer: brauer.c binaryOperation.o
	$(CC) brauer.c  binaryOperation.o $(ARGS) -o brauer 

squareMultiply: squareMultiply.c binaryOperation.o montgomery.o extendedEuclid.o
	$(CC) squareMultiply.c binaryOperation.o montgomery.o extendedEuclid.o $(ARGS) -o squareMultiply

clear:
	rm *.o karatsuba brauer squareMultiply
