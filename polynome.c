#include "polynome.h"

void init_poly_zero(Poly* p, uint degree)
{
  p->degree = degree;
  p->data = calloc(degree+1,sizeof(uint));
}

void init_poly(Poly* p, uint* coeffs, uint degree)
{
  p->degree = degree;
  p->data = coeffs;
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
  result->data = malloc(sizeof(uint)*(result->degree+1));
  uint i;
  for(i=0;i<b.degree+1;i++)
    result->data[i] = a.data[i] + b.data[i]; 
  while(i<a.degree+1)
  {
  	result->data[i] = a.data[i];
	i++;
  }
  return *result;
}

Poly negativePoly(Poly p)
{
	Poly* result = malloc(sizeof(Poly));
	uint i;
	result->degree = p.degree;
	result->data = malloc(sizeof(uint)*(result->degree+1));
	for(i=0;i<p.degree+1;i++)
		result->data[i]= -p.data[i];
	return *result;
}

Poly shiftPoly(Poly *a,uint shift)
{
  uint i, newDegree=a->degree+shift;
  uint* newData=calloc(newDegree+1,sizeof(uint));
  for(i=0;i<a->degree+1;i++)
    newData[i+shift] = a->data[i];
  a->degree = newDegree;
  a->data = newData;
  return *a;
}

//return two polynomes of degree deg(p)/2
Poly* dividePoly(Poly p)
{
	Poly* result = malloc(sizeof(Poly)*2);
	uint i, newdegree=p.degree/2;

	for(i=0;i<2;i++)
	{
		result[i].degree = newdegree;
		result[i].data = malloc(sizeof(uint)*(newdegree+1));
	}

	for(i=0;i<newdegree+1;i++)
	{
		result[0].data[i]=p.data[i];
		result[1].data[i]=p.data[i+newdegree+1];
	}
	return result;
}

void freePoly(Poly p)
{
	free(p.data[0]);
	free(p.data[1]);
	free(p);
}
