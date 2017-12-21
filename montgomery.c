#include "montgomery.h"
//we assume p odd
uint reduc_Montgomery(uint m, uint p, uint n, uint inv_p)
{
  int Q = m*inv_p;
  return (m-Q*p)>>n ;
}

void reduc_Montgomery_gmp(mpz_t result, mpz_t m, mpz_t p, uint n, mpz_t inv_p)
{
	mpz_t Q,product,N,ninv_p;

	mpz_init(ninv_p);
	mpz_t exp2n;
	mpz_init_set_ui(exp2n,1);
	mpz_mul_2exp(exp2n,exp2n,n);
	mpz_sub(ninv_p,exp2n,inv_p);

	mpz_init_set_ui(N,1);
	mpz_mul_2exp(N,N,n);

	mpz_init(Q);
	mpz_mul(Q,m,ninv_p);
	mpz_mod(Q,Q,N);

	mpz_init(product);
	mpz_mul(product,Q,p);
	mpz_add(result,m,product);
	mpz_tdiv_q_2exp(result,result,n);
	if( mpz_cmp(result,p) >= 0 )
		mpz_sub(result,result,p);
	mpz_clear(Q);
	mpz_clear(product);
}

uint repr_Montgomery(uint x,uint p, uint n)
{
	return ( x<<n )%p;
}

void repr_Montgomery_gmp(mpz_t result,mpz_t x,mpz_t p, uint n)
{
	mpz_mul_2exp(result,x,n);
	mpz_mod(result,result,p);
}
