#include <stdio.h>
#include "arrayUtil.h"

int areEqual(ArrayUtil a, ArrayUtil b){
	int i, length = a.typeSize*a.length;
	char c1, c2;

	if(a.length != b.length || a.typeSize != b.typeSize){
		return 0;
	}

	for (i = 0; i < length; ++i)
	{
		c1 = ((char*)a.base)[i];
		c2 = ((char*)b.base)[i];
		if(c1 != c2){
			return 0;
		}
	}
	return 1;
}

ArrayUtil create(int typeSize, int length){
	ArrayUtil a;
	int i;
	a.typeSize = typeSize;
	a.length = length;
	a.base = malloc(length*typeSize);
	for (i = 0; i < (length*typeSize); ++i)
	{
		((char*)a.base)[i] = 0;
	}
	return a;
}


