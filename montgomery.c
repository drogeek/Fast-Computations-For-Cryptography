#include <stdio.h>
#include <stdlib.h>
#include "extendedEuclid.h"

typedef unsigned int uint;

#define DEFAULT_PW_R 5

uint REDC(const uint t,const uint r,const uint n,const int neg_inv_n)
{
	printf("t=%u\n",t);
	printf("invn=%d", (neg_inv_n*n)%r);
	uint res;
	uint m = ((t%r)*neg_inv_n)%r;
	res = (t+m*n)<<r;
	if (res >= n)
		return res-n;
	else
		return res;
}

uint bin_Size(int nbr)
{
  uint result=0;
  while(nbr)
  {
    nbr>>=1;
    result++;
  }
  return result;
}

//we assume p odd
uint reduction_Montgomery(uint m, uint p)
{
  uint n = bin_Size(p)*2;
  ExtEucRes extEucRes = extendedEuclid(p,1<<n);
  int Q = m*extEucRes.u;
  return ( m-Q*p*extEucRes.v )%p;
}

uint repr_Montgomery(uint x,uint p, uint n)
{
	x=( x<<n )%p;
}

int main(int argc, char** argv)
{
	//ExtEucRes extEucRes;
	/*
	uint powerOfTwo=DEFAULT_PW_R;
	do
	//we wanta power of 2 that is coprime with n
	//note that this is useless if n is odd
	while(extEucRes.r-1)
	{
		extEucRes=extendedEuclid(1<<powerOfTwo,n);
		powerOfTwo++;
	}
	
	uint N=17,R=10;
	uint a=repr_Montgomery(7,R,N);
	printf("a=%u\n",a);
	uint b=repr_Montgomery(15,R,N);
	printf("b=%u\n",b);
	extEucRes=extendedEuclid(R,N);
	printf("%u %d %d\n", extEucRes.r, extEucRes.u, extEucRes.v);
	printf("%u\n",REDC(a*b,R,N,extEucRes.v));
	*/

  printf("%d\n", reduction_Montgomery(156,17));
  return EXIT_SUCCESS;
}
