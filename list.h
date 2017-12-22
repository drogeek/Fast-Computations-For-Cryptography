#ifndef _LIST
#define _LIST


#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;
typedef struct _listChar
{
	char* data;
	uint size;
	uint ptr;
}ListC;


void initListC(ListC* l, uint size);
void appendListC(ListC* l, char val);
#endif
