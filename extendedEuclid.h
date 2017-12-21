#ifndef _EXTEUCLID_
#define _EXTEUCLID_
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
typedef unsigned int uint;
typedef struct _extEucRes
{
  uint r;
  int u;
  int v;
}ExtEucRes;

typedef struct _extEucResGMP
{
  mpz_t r;
  mpz_t u;
  mpz_t v;
}ExtEucResGMP;

ExtEucRes extendedEuclid(int a, int b);
ExtEucResGMP extendedEuclid_gmp(mpz_t a, mpz_t b);
void reallignExtEuc_gmp(ExtEucResGMP* e, mpz_t a, mpz_t b);

#endif
