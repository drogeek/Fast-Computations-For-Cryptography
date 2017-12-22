#ifndef _POLY_
#define _POLY_
#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;
typedef struct
{
  uint degree;
  //from least to most representative degree
  uint* data;
}Poly;

void init_poly(Poly* p, uint* coeffs, uint degree);
void init_poly_zero(Poly* p, uint degree);
Poly addPoly(Poly a, Poly b);
Poly shiftPoly(Poly *a,uint shift);
Poly* dividePoly(Poly p);
Poly negativePoly(Poly p);
void freePoly(Poly p);


#endif
