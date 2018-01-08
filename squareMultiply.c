#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "binaryOperation.h"
#include "montgomery.h"
#include "mersenne.h"

void SM_RtoL(mpz_t y, mpz_t x, mpz_t e, mpz_t p)
{
	mpz_t rx,neg_inv_p;
	uint n;
		
	mpz_init(neg_inv_p);
	n=init_Montgomery_gmp(neg_inv_p,p);	

	mpz_set_ui(y,1);
	repr_Montgomery_gmp(y,y,p,n);

	mpz_init(rx);
	repr_Montgomery_gmp(rx,x,p,n);
	//we get a decomposition of e in base 2^{1}
	BaseW bin_e=decomp_base_2expw(e,1);

	uint i;
	for(i=0;i<bin_e.degree;i++)
	{
		if( bin_e.coeffs[i] )
		{
			mpz_mul(y,y,rx);
			reduc_Montgomery_gmp(y,y,p,n,neg_inv_p);
		}
		mpz_mul(rx,rx,rx);
		reduc_Montgomery_gmp(rx,rx,p,n,neg_inv_p);
	}
	reduc_Montgomery_gmp(y,y,p,n,neg_inv_p);

	mpz_clear(rx);
}

void SM_LtoR(mpz_t y, mpz_t x, mpz_t e, mpz_t p)
{
	mpz_t rx,neg_inv_p;
	uint n;
		
	mpz_init(neg_inv_p);
	n=init_Montgomery_gmp(neg_inv_p,p);	

	mpz_set_ui(y,1);
	repr_Montgomery_gmp(y,y,p,n);

	mpz_init(rx);
	repr_Montgomery_gmp(rx,x,p,n);
	//we get a decomposition of e in base 2^{1}
	BaseW bin_e=decomp_base_2expw(e,1);

	int i;
	for(i=bin_e.degree-1;i>=0;i--)
	{
		mpz_mul(y,y,y);
		reduc_Montgomery_gmp(y,y,p,n,neg_inv_p);
		if( bin_e.coeffs[i] )
		{
			mpz_mul(y,y,rx);
			reduc_Montgomery_gmp(y,y,p,n,neg_inv_p);
		}
	}
	reduc_Montgomery_gmp(y,y,p,n,neg_inv_p);

	mpz_clear(rx);
}

void SM_RtoL_mersenne(mpz_t y, mpz_t x, mpz_t e, mpz_t p, uint n)
{
	mpz_t rx;
		
	mpz_set_ui(y,1);

	mpz_init_set(rx,x);

	//we get a decomposition of e in base 2^{1}
	BaseW bin_e=decomp_base_2expw(e,1);

	uint i;
	for(i=0;i<bin_e.degree;i++)
	{
		if( bin_e.coeffs[i] )
		{
			mpz_mul(y,y,rx);
      mersenne_gmp(y,y,n,p);
		}
		mpz_mul(rx,rx,rx);
    mersenne_gmp(rx,rx,n,p);
	}
  mersenne_gmp(y,y,n,p);

	mpz_clear(rx);
}

int main(void)
{
	mpz_t x,e,p,result;
	mpz_init(result);
	mpz_init_set_str(x,"125534556856255274",10);
	mpz_init_set_str(e,"5348787361364867687",10);
	//p must be odd!
	mpz_init_set_str(p,"79228162514264337593543950335",10);
  /*
	SM_RtoL(result,x,e,p);
	gmp_printf("%Zd\n",result);
	SM_LtoR(result,x,e,p);
	gmp_printf("%Zd\n",result);
  */
  SM_RtoL_mersenne(result,x,e,p,96);
	//gmp_printf("%Zd\n",result);
	return EXIT_SUCCESS;
}
