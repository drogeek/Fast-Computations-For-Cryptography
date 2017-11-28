#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;
typedef struct
{
  uint degree;
  uint* data;
}Poly;

void init_poly(Poly* p, uint* coeffs, uint degree);
void init_poly_zero(Poly* p, uint degree);
Poly addPoly(Poly a, Poly b);
void shiftPoly(Poly *a,uint shift);

int main(void)
{
  Poly p,p1;
  uint data[] = { 2, 1, 1, 3, 5 };
  uint data2[] = { 2, 1, 1, 3, 5 };
  init_poly(&p1,data2,4);
  init_poly(&p,data,4);
  uint i;
  shiftPoly(&p,4);
  Poly p2 = addPoly(p,p1);
  for(i=0; i<p2.degree+1; i++)
    printf("%d\n",p2.data[i]);
  return EXIT_SUCCESS;
}

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

void shiftPoly(Poly *a,uint shift)
{
  uint i, newDegree=a->degree+shift;
  uint* newData=calloc(newDegree+1,sizeof(uint));
  for(i=0;i<a->degree+1;i++)
    newData[i+shift] = a->data[i];
  a->degree = newDegree;
  a->data = newData;
}
