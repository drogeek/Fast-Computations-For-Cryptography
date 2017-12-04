#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

typedef unsigned int uint;
typedef struct
{
  uint degree;
  //from least to most representative degree
  mpz_t* data;
}Poly;

void init_poly(Poly* p, uint* coeffs, uint degree);
void init_poly_zero(Poly* p, uint degree);
Poly addPoly(Poly a, Poly b);
Poly shiftPoly(Poly *a,uint shift);
Poly* dividePoly(Poly p);
Poly karatsuba(Poly a, Poly b);
Poly negativePoly(Poly p);
void printPoly(Poly p);

int main(void)
{
  Poly p,p1,result;
  uint data[] = { 1, 1, 3, 5 };
  uint data2[] = { 2, 1, 1, 3 };
  init_poly(&p1,data2,3);
  init_poly(&p,data,3);
  result = karatsuba(p,p1);
  printPoly(result);
  return EXIT_SUCCESS;
}

void printPoly(Poly p)
{
  uint i;
  for (i=0;i<p.degree+1;i++)
  {
    printf(mpz_get_str(NULL,10,p.data[i]));
	printf(" ");
  }
}

void init_poly_zero(Poly* p, uint degree)
{
  p->degree = degree;
  p->data = malloc(sizeof(mpz_t)*(degree+1));
  uint i;
  for(i=0;i<degree+1;i++)
  	mpz_init(p->data[i]);
}

void init_poly(Poly* p, uint* coeffs, uint degree)
{
	init_poly_zero(p,degree);
	uint i;
	for (i=0;i<p->degree+1;i++)
		mpz_set_ui(p->data[i],coeffs[i]);
}

Poly addPoly(Poly a, Poly b)
{
  Poly* result = malloc(sizeof(Poly));
  // we exchange a and b to ensure deg(a) >= deg(b)
  if(a.degree < b.degree)
  {
  	Poly tmp = a;
	a=b;
	b=tmp;
  }

  result->degree = a.degree;
  result->data = malloc(sizeof(mpz_t)*(result->degree+1));
  uint i;
  for(i=0;i<b.degree+1;i++)
  	mpz_add(result->data[i],a.data[i],b.data[i]);
  while(i<a.degree+1)
  {
  	mpz_set(result->data[i],a.data[i]);
	i++;
  }
  return *result;
}

Poly negativePoly(Poly p)
{
	Poly* result = malloc(sizeof(Poly));
	uint i;
	result->degree = p.degree;
	result->data = malloc(sizeof(mpz_t)*(result->degree+1));
	for(i=0;i<p.degree+1;i++)
		mpz_neg(result->data[i],p.data[i]);
	return *result;
}

Poly shiftPoly(Poly *a,uint shift)
{
  uint i, newDegree=a->degree+shift;

  //we save the data, we'll need it right after
  Poly savedPoly;
  savedPoly.degree = a->degree;
  savedPoly.data = a->data;

  init_poly_zero(a,newDegree);

  for(i=0;i<savedPoly.degree+1;i++)
    mpz_set(a->data[i+shift], savedPoly.data[i]);
  return *a;
}

//return two polynomes of degree deg(p)/2
Poly* dividePoly(Poly p)
{
	Poly* result = malloc(sizeof(Poly)*2);
	uint i, newdegree=p.degree/2;

	for(i=0;i<2;i++)
		init_poly_zero(&result[i],newdegree);

	for(i=0;i<newdegree+1;i++)
	{
		mpz_set(result[0].data[i],p.data[i]);
		mpz_set(result[1].data[i],p.data[i+newdegree+1]);
	}
	return result;
}

Poly karatsuba(Poly a, Poly b)
{
	Poly *result=malloc(sizeof(Poly));
	if(a.degree == 0)
	{
		init_poly_zero(result,0);
		mpz_mul(result->data[0],a.data[0],b.data[0]);
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
