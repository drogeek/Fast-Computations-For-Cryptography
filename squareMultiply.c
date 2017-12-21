#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "binaryOperation.h"
#include "montgomery.h"

void SM_RtoL(mpz_t y, mpz_t x, mpz_t e, mpz_t p)
{
	mpz_set_ui(y,1);
	uint n = bin_Size_gmp(p);
	repr_Montgomery_gmp(y,y,p,n);
	mpz_t rx, twopown;
	mpz_init(rx);
	mpz_init_set_ui(twopown,1);
	mpz_mul_2exp(twopown,twopown,n);
	ExtEucResGMP extEucRes= extendedEuclid_gmp(p,twopown);
	repr_Montgomery_gmp(rx,x,p,n);
	BaseW bin_e=decomp_base_2expw(e,1);

	uint i;
	for(i=0;i<bin_e.degree;i++)
	{
		if( bin_e.coeffs[i] )
		{
			mpz_mul(y,y,rx);
			reduc_Montgomery_gmp(y,y,p,n,extEucRes.u);
		}
		mpz_mul(rx,rx,rx);
		reduc_Montgomery_gmp(rx,rx,p,n,extEucRes.u);
	}
	mpz_clear(rx);
	mpz_clear(twopown);
	reduc_Montgomery_gmp(y,y,p,n,extEucRes.u);
}

int main(void)
{
	mpz_t x,e,p,result;
	mpz_init(result);
	mpz_init_set_str(x,"125534",10);
	mpz_init_set_str(e,"53",10);
	//p must be odd!
	mpz_init_set_str(p,"15",10);
	SM_RtoL(result,x,e,p);
	gmp_printf("%Zd\n",result);
	return EXIT_SUCCESS;
}
