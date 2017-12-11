#ifndef _EXTEUCLID_
#define _EXTEUCLID_
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int uint ;
typedef struct _extEucRes
{
  uint r;
  uint u;
  uint v;
}ExtEucRes;

ExtEucRes extendedEuclid(uint a, uint b);

#endif
