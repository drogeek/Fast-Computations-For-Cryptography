#include <stdio.h>
#include <stdlib.h>
#include "list.h"
typedef unsigned int uint;
typedef struct _naf
{
	char* coeffs;
	uint size;
}NafRes;

NafRes naf(uint nbr)
{
	uint i=0;
	NafRes result;
	ListC list;
	initListC(&list,2);

	while(nbr>=1)
	{
		if(nbr&1)
		{
			appendListC(&list,2-(nbr&3));
			nbr-=list.data[i];
		}
		else
			appendListC(&list,0);
		nbr>>=1;
		i++;
	}
	result.size=list.ptr+1;
	result.coeffs=list.data;
	return result;
}

int main(void)
{
	NafRes res = naf(503);
	uint i;
	for(i=0;i<res.size;i++)
		printf("(%u,%d)\n",i,res.coeffs[i]);
	return EXIT_SUCCESS;
}
