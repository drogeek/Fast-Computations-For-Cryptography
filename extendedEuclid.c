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
