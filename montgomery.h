#ifndef __MONTGOMERY__
#define __MONTGOMERY__

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "binaryOperation.h"
#include "extendedEuclid.h"


typedef unsigned int uint;

uint reduc_Montgomery(uint m, uint p, uint n, uint inv_p);
void reduc_Montgomery_gmp(mpz_t result,mpz_t m, mpz_t p, uint n, mpz_t inv_p);
uint repr_Montgomery(uint x,uint p, uint n);
void repr_Montgomery_gmp(mpz_t result,mpz_t x,mpz_t p, uint n);
#endif


