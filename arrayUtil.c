#include <stdio.h>
#include <string.h>
#include "arrayUtil.h"

void* reduce(ArrayUtil util, ReducerFunc* reducer, void* hint, void* intialValue){
	int i;
	void *this,*pv = intialValue;
	for (i = 0; i < util.length; ++i){
		this = traverse(&util, i);
		pv = reducer(hint, pv, this);
	}
	return pv;
}

int areEqual(ArrayUtil a, ArrayUtil b){
	int i, length = a.typeSize*a.length;
	char *base1 = ((char*)a.base), *base2 = ((char*)b.base);

	if(a.length != b.length || a.typeSize != b.typeSize) return 0;

	for (i = 0; i < length; ++i){
		if(base1[i] != base2[i]) return 0;
	}
	return 1;
}

ArrayUtil create(int typeSize, int length){
	ArrayUtil a;
	a.typeSize = typeSize;
	a.length = length;
	a.base = calloc(length, typeSize);
	return a;
}

void setZero(void *ptr, int from ,int length){
	int i;
	for (i = from; i < length; ++i)
	{
		((char*)ptr)[i] = '\0';
	}
}

ArrayUtil resize(ArrayUtil array, int length) {
	int diffrence;
	void *temp;
	if(array.length < length){
		temp = calloc(length, array.typeSize);
		memcpy(temp, array.base, array.length*array.typeSize);
		array.length = length;
		array.base = temp;
		return array;
	}
	else if(array.length > length){
		temp = calloc(length, array.typeSize);
		memcpy(temp, array.base, length*array.typeSize);
		array.length = length;
		array.base = temp;
	}
	return array;
	
}

void dispose(ArrayUtil util){
	free(util.base);
}

void* findLast(ArrayUtil util, MatchFunc* match, void* hint){
	int i;
	void *this;
	for (i = util.length-1; i >= 0; --i) {
		this = traverse(&util, i);
		if(match(hint,this)) return this;
	}
}

void* findFirst(ArrayUtil util, MatchFunc* match, void* hint){
	int i;
	void *this;
	for (i = 0; i < util.length; ++i)
	{
		this = traverse(&util, i);
		if(match(hint,this)) return this;
	}
}

int count(ArrayUtil util, MatchFunc* match, void* hint){
	int i,doesMatch,counter=0;
	for (i = 0; i < util.length; ++i){
		match(hint,traverse(&util,i)) ? counter++ : counter;
	}	
	return counter;
}

void* traverse(ArrayUtil *util,int index){
	return (*util).base+((*util).typeSize*index);
}

int filter(ArrayUtil util, MatchFunc* match, void* hint, void** destination, int maxItems){
	int i,doesMatch,counter=0,j,bytes=0;
	void *result=null,*this;
	for (i = 0; i < util.length; ++i) {
		this = traverse(&util, i); //util.base+(util.typeSize*i);
		doesMatch = match(hint,this);
		if(doesMatch){
			counter++;
			result = (void*)realloc(result, util.typeSize*counter);
			for (j = 0; j < util.typeSize; ++j){
				((char*) result)[bytes++] = ((char*)this)[j];
			}
		}
	}
	*destination = result;
	return counter;
}

void map(ArrayUtil source, ArrayUtil destination, ConvertFunc* convert, void* hint){
	int i;
	void *this, *destinationItem;
	for (i = 0; i < source.length; ++i){
		this = traverse(&source, i);
		destinationItem = traverse(&destination, i);
		convert(hint, this, destinationItem);	
	}
}

void forEach(ArrayUtil util, OperationFunc* operation, void* hint){
	int i;
	void *this;
	for (i = 0; i < util.length; ++i){
		this = traverse(&util, i);
		operation(hint, this);
	}
}