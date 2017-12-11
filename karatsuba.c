#include <stdio.h>
#include <stdlib.h>
#include "polynome.h"


Poly karatsuba(Poly a, Poly b);

int main(void)
{
  Poly p,p1,result;
  uint data[] = { 1, 1, 3, 5 };
  uint data2[] = { 2, 1, 1, 3 };
  init_poly(&p1,data2,3);
  init_poly(&p,data,3);
  uint i;
  result = karatsuba(p,p1);
  for (i=0;i<result.degree+1;i++)
    printf("%d\n",result.data[i]);
  return EXIT_SUCCESS;
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
