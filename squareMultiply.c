#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "binaryOperation.h"
#include "montgomery.h"

void SM_RtoL(mpz_t y, mpz_t x, mpz_t e, mpz_t p)
{
	mpz_t rx, twoPowN,neg_inv_p;
	uint n = bin_Size_gmp(p);

	mpz_set_ui(y,1);
	repr_Montgomery_gmp(y,y,p,n);

	//we compute -p^{-1} mod 2^{n}
	mpz_init_set_ui(twoPowN,1);
	mpz_mul_2exp(twoPowN,twoPowN,n);
	ExtEucResGMP extEucRes= extendedEuclid_gmp(p,twoPowN);
	mpz_init(neg_inv_p);
	mpz_sub(neg_inv_p,twoPowN,extEucRes.u);

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
	mpz_clear(twoPowN);
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
