#include "binaryOperation.h"

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

uint bin_Size_gmp(mpz_t nbr)
{
  uint size=0;
  mpz_t tmp;  
  mpz_init_set(tmp,nbr);

  while(mpz_cmp_ui(tmp,0))
  {
    mpz_tdiv_q_2exp(tmp,tmp,1);
    size++;
  }
  return size;
}

// w must be > 32
BaseW decomp_base_2expw(mpz_t nbr, uint w)
{
  BaseW result;
  result.w=w;
  mpz_t cpy,tmp,mask;
  mpz_init(tmp);
  mpz_init_set(cpy,nbr);

  uint size=bin_Size_gmp(nbr);
  if( size%w )
    result.degree = size/w+1;
  else
    result.degree = size/w;
  result.coeffs = malloc(sizeof(mpz_t)*result.degree);

  uint i;
  mpz_init_set_ui(mask,(1<<w)-1);
  for(i=0;i<result.degree;i++)
  {
    mpz_and(tmp,cpy,mask);
    result.coeffs[i] = mpz_get_ui(tmp);
    mpz_tdiv_q_2exp(cpy,cpy,w);
  }
  return result;
}
