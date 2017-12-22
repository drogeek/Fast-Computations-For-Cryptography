#include "extendedEuclid.h"

ExtEucRes extendedEuclid(int a, int b)
{
  ExtEucRes res;
  int r1=a,r2=b,u1=1,u2=0,v1=0,v2=1;
  int q,rs,us,vs;
  while(r2)
  {
    q=r1/r2;

    rs=r1;
    us=u1;
    vs=v1;

    r1=r2;
    u1=u2;
    v1=v2;

    r2=rs-q*r2;
    u2=us-q*u2;
    v2=vs-q*v2;
  }
  res.r=r1;
  res.u=u1;
  res.v=v1;
  return res;
}

ExtEucResGMP extendedEuclid_gmp(mpz_t a, mpz_t b)
{
  ExtEucResGMP res;
  mpz_t r1,r2,u1,u2,v1,v2,q,rs,us,vs,product;
  mpz_init_set(r1,a);
  mpz_init_set(r2,b);
  mpz_init_set_ui(u1,1);
  mpz_init_set_ui(u2,0);
  mpz_init_set_ui(v1,0);
  mpz_init_set_ui(v2,1);
  mpz_init(q);
  mpz_init(rs);
  mpz_init(us);
  mpz_init(vs);
  mpz_init(product);
  while(mpz_cmp_ui(r2,0))
  {
  	mpz_tdiv_q(q,r1,r2);

	mpz_set(rs,r1);
	mpz_set(us,u1);
	mpz_set(vs,v1);

	mpz_set(r1,r2);
	mpz_set(u1,u2);
	mpz_set(v1,v2);

	mpz_mul(product,q,r2);
	mpz_sub(r2,rs,product);
	mpz_mul(product,q,u2);
	mpz_sub(u2,us,product);
	mpz_mul(product,q,v2);
	mpz_sub(v2,vs,product);
  }
  mpz_init_set(res.r,r1);
  mpz_init_set(res.u,u1);
  mpz_init_set(res.v,v1);
  mpz_clear(r1);
  mpz_clear(r2);
  mpz_clear(u1);
  mpz_clear(u2);
  mpz_clear(v1);
  mpz_clear(v2);
  mpz_clear(q);
  mpz_clear(rs);
  mpz_clear(us);
  mpz_clear(vs);
  mpz_clear(product);
  reallignExtEuc_gmp(&res,a,b);
  return res;
}

//we make sure that 
//u*a % b = 1 with 0<=u<b
//v*b % a = 1 with 0<=v<a
void reallignExtEuc_gmp(ExtEucResGMP* e, mpz_t a, mpz_t b)
{
	while(mpz_cmp_ui(e->u,0) < 0)
		mpz_add(e->u, e->u, b);
	while(mpz_cmp_ui(e->v,0) < 0)
		mpz_add(e->v, e->v, a);
	while(mpz_cmp(e->u,b) >= 0)
		mpz_sub(e->u, e->u, b);
	while(mpz_cmp(e->v,a) >= 0)
		mpz_sub(e->v, e->v, a);
}
