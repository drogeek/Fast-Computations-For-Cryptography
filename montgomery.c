#include "montgomery.h"
//we assume p odd
uint reduc_Montgomery(uint m, uint p, uint n, uint neg_inv_p)
{
  uint mask_modulus = (1<<n)-1;
  uint Q = (m*neg_inv_p)&mask_modulus;
  return (m+Q*p)>>n ;
}

void reduc_Montgomery_gmp(mpz_t result, mpz_t m, mpz_t p, uint n, mpz_t neg_inv_p)
{
	mpz_t Q,product,mask_modulus;

	//we create a mask 2^{n}-1
	mpz_init_set_ui(mask_modulus,1);
	mpz_mul_2exp(mask_modulus,mask_modulus,n);
	mpz_sub_ui(mask_modulus,mask_modulus,1);

	//we compute Q = m*-p^{-1} mod 2^{n}
	mpz_init(Q);
	mpz_mul(Q,m,neg_inv_p);
	mpz_and(Q,Q,mask_modulus);
	
	//we compute (m+Qp)/2^{n} = m*(2^{n})^{-1} mod p
	mpz_init(product);
	mpz_mul(product,Q,p);
	mpz_add(result,m,product);
	mpz_tdiv_q_2exp(result,result,n);

	//0 <= result < 2*p
	if( mpz_cmp(result,p) >= 0 )
		mpz_sub(result,result,p);

	mpz_clear(Q);
	mpz_clear(product);
	mpz_clear(mask_modulus);
}

uint repr_Montgomery(uint x,uint p, uint n)
{
	return (x<<n)%p;
}

//stores -p^{-1} mod 2^{n} in neg_inv_p and returns size of p
uint init_Montgomery_gmp(mpz_t neg_inv_p, mpz_t p)
{
	uint n = bin_Size_gmp(p);
	mpz_t twoPowN;
	//we compute -p^{-1} mod 2^{n}
	mpz_init_set_ui(twoPowN,1);
	mpz_mul_2exp(twoPowN,twoPowN,n);
	ExtEucResGMP extEucRes= extendedEuclid_gmp(p,twoPowN);
	mpz_sub(neg_inv_p,twoPowN,extEucRes.u);
	mpz_clear(twoPowN);
	return n;
}

void repr_Montgomery_gmp(mpz_t result,mpz_t x,mpz_t p, uint n)
{
	mpz_mul_2exp(result,x,n);
	mpz_mod(result,result,p);
}
