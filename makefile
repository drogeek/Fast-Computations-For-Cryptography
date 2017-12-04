ARGS=-Wall -Wextra -lgmp -g
karatsuba: karatsuba.c
	gcc karatsuba.c $(ARGS) -o karatsuba
