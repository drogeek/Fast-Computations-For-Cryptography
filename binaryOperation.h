#ifndef _BINOP_
#define _BINOP_
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

typedef struct _baseW
{
  uint* coeffs;
  uint degree;
  uint w;
}BaseW;

uint bin_Size(int nbr);
uint bin_Size_gmp(mpz_t nbr);
BaseW decomp_base_2expw(mpz_t nbr, uint w);
#endif
