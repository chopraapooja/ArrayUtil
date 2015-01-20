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
	int i,bytes = length*typeSize;

	a.typeSize = typeSize;
	a.length = length;
	a.base = malloc(bytes);

	for (i = 0; i < (bytes); ++i)
	{
		((char*)a.base)[i] = '\0';
	}
	return a;
}

void setZero(void *ptr, int length){
	int i;
	for (i = 0; i < length; ++i)
	{
		((char*)ptr)[i] = '\0';
	}
}

ArrayUtil resize(ArrayUtil array, int length) {
	int diffrence;
	if(array.length < length){
		array.base = realloc(array.base, length*array.typeSize);
		setZero(array.base, length*array.typeSize);
		array.length = length;
		return array;
	}
	else if(array.length > length){
		array.length = length;
		return array;
	}else{
		return array;
	}
}

void dispose(ArrayUtil util){
	free(util.base);
}

