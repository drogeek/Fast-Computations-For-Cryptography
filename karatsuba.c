#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "polynome.h"
#include "binaryOperation.h"


Poly karatsuba(Poly a, Poly b);
Poly convertToPoly( mpz_t nbr, uint sizeCoeff );
void convertToNbr(mpz_t result, Poly p, uint sizeCoeff);

int main(void)
{
  mpz_t a,b,resultNbr;
  mpz_init(resultNbr);
  //to simplify, karatsuba takes only polynomes of degree 2^{t}-1
  //we then have to select a, b and w such that when a and b are divided by w, we get 2^{t} parts
  //here I took a = 2^{8*4}-1 (size 2^{8*4}) and I substracted 2^{31} to a to get b
  mpz_init_set_str(a,"4294967295",10);
  mpz_init_set_str(b,"2147483647",10);
  Poly p,p1,result;
  uint w=8;
  p=convertToPoly(a,w);
  p1=convertToPoly(b,w);
  result = karatsuba(p,p1);
  convertToNbr(resultNbr,result,w);
  gmp_printf("%Zd\n", resultNbr);
  /*
  uint i;
  for (i=0;i<result.degree+1;i++)
    printf("%d\n",result.data[i]);
	*/
  return EXIT_SUCCESS;
}

Poly convertToPoly( mpz_t nbr, uint sizeCoeff )
{
	Poly* result = malloc(sizeof(Poly));
	BaseW tmp=decomp_base_2expw(nbr,sizeCoeff);
	result->data = tmp.coeffs;
	result->degree = tmp.degree-1;
	return *result;
}

void convertToNbr(mpz_t result, Poly p, uint sizeCoeff)
{
	uint i;
	mpz_t tmp;
	mpz_init(tmp);
	mpz_set_ui(result,0);

	for(i=0;i<p.degree+1;i++)
	{
		mpz_set_ui(tmp,p.data[i]);
		mpz_mul_2exp(tmp,tmp,i*sizeCoeff);
		mpz_add(result,result,tmp);
	}
}

Poly karatsuba(Poly a, Poly b)
{
	Poly *result=malloc(sizeof(Poly));
	if(a.degree == 0)
	{
		result->data = malloc(sizeof(uint));
		result->data[0] = a.data[0] * b.data[0];
	}

	else
	{
		Poly* divided_a = dividePoly(a);
		Poly* divided_b = dividePoly(b);
		Poly p2 = karatsuba(divided_a[1],divided_b[1]);
		Poly p0 = karatsuba(divided_a[0],divided_b[0]);
		Poly p1 = karatsuba(addPoly(divided_a[1],divided_a[0]), addPoly(divided_b[1],divided_b[0]));
		p1 = addPoly(p1,negativePoly(addPoly(p2,p0)));
		*result = addPoly(addPoly(shiftPoly(&p2,a.degree+1),shiftPoly(&p1,(a.degree+1)/2)),p0);
		free(divided_a);
		free(divided_b);
	}
	return *result;
}
