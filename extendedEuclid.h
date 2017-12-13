#ifndef _EXTEUCLID_
#define _EXTEUCLID_
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int uint;
typedef struct _extEucRes
{
  uint r;
  int u;
  int v;
}ExtEucRes;

ExtEucRes extendedEuclid(int a, int b);

#endif
