#include "list.h"

void initListC(ListC* l, uint size)
{
	l->size=size;
	l->data = malloc(sizeof(char)*size);
	l->ptr=0;
}

void appendListC(ListC* l, char val)
{
	if(l->ptr == l->size)
	{
		l->size<<=1;
		realloc(l->data,l->size);
	}

	l->data[l->ptr]=val;
	l->ptr++;
}
