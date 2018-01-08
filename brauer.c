#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "binaryOperation.h"
#include "mersenne.h"

void brauer(mpz_t y,mpz_t x, BaseW nbr, mpz_t p)
{
  mpz_init_set_ui(y,1);
  mpz_t* precalculs = malloc(sizeof(mpz_t)*(1<<nbr.w));
  mpz_init_set_ui(precalculs[0],1);

  int i,j;
  //we precompute [x^1,…,x^{2^{w}-1}]
  for(i=1;i<1<<nbr.w;i++)
  {
    mpz_init(precalculs[i]);
    mpz_mul(precalculs[i],precalculs[i-1],x);
    mpz_mod(precalculs[i],precalculs[i],p);
  }

  mpz_set(y,precalculs[nbr.coeffs[nbr.degree-1]]);
  for(i=nbr.degree-2;i>=0;i--)
  {
    for(j=0;j<nbr.w;j++)
	{
      mpz_mul(y,y,y);
	  mpz_mod(y,y,p);
  	}
    mpz_mul(y,y,precalculs[nbr.coeffs[i]]);
    mpz_mod(y,y,p);
  }
  for(i=0;i<1<<nbr.w;i++)
  	mpz_clear(precalculs[i]);
  free(precalculs);
}

void brauer_mersenne(mpz_t y,mpz_t x, BaseW nbr, mpz_t p, uint n)
{
  mpz_init_set_ui(y,1);
  mpz_t* precalculs = malloc(sizeof(mpz_t)*(1<<nbr.w));
  mpz_init_set_ui(precalculs[0],1);

  int i,j;
  //we precompute [x^1,…,x^{2^{w}-1}]
  for(i=1;i<1<<nbr.w;i++)
  {
    mpz_init(precalculs[i]);
    mpz_mul(precalculs[i],precalculs[i-1],x);
    mersenne_gmp(precalculs[i],precalculs[i],n,p);
  }

  mpz_set(y,precalculs[nbr.coeffs[nbr.degree-1]]);
  for(i=nbr.degree-2;i>=0;i--)
  {
    for(j=0;j<nbr.w;j++)
	{
      mpz_mul(y,y,y);
	  mpz_mod(y,y,p);
	  mersenne_gmp(y,y,n,p);
  	}
    mpz_mul(y,y,precalculs[nbr.coeffs[i]]);
    mersenne_gmp(y,y,n,p);
  }

  for(i=0;i<1<<nbr.w;i++)
  	mpz_clear(precalculs[i]);
  free(precalculs);
}

int main(int argc, char** argv)
{
  uint w=atoi(argv[1]);
  mpz_t a,b,p,result,test;  
  mpz_init(result);
  mpz_init(test);
  mpz_init_set_str(a,"193453341234123412341234123412341235",10);
  mpz_init_set_str(b,"2345226896544787654345678765433223",10);
  mpz_init_set_str(p,"79228162514264337593543950335",10);
  brauer(result,a,decomp_base_2expw(b,w),p);
  //gmp_printf("%Zd\n", result);
  /*
  printf("\n");
  mpz_powm(test,a,b,p);
  mpz_out_str(stdout,10,test);
  printf("\n");
  */
  return EXIT_SUCCESS;
}
