#include <assert.h>
#include "arrayUtil.h"

void test_areEqual_should_return_1_when_both_comparable_arrays_are_of_same_length_typeSize_and_having_same_elements(){
	ArrayUtil arr1, arr2;
	int a1[] = {1,2,3};
	int a2[] = {1,2,3};

	arr1.length = 3;
	arr2.length = 3;

	arr1.typeSize = 4;
	arr2.typeSize = 4;


	arr1.base = a1;
	arr2.base = a2;

	assert(areEqual(arr1, arr2) == 1);
}

void test_areEqual_should_return_0_when_both_comparable_arrays_are_of_same_length_typeSize_but_having_different_elements(){
	ArrayUtil arr1, arr2;
	int a1[] = {1,2,3};
	int a2[] = {1,2,0};

	arr1.length = 3;
	arr2.length = 3;

	arr1.typeSize = 4;
	arr2.typeSize = 4;


	arr1.base = a1;
	arr2.base = a2;

	assert(areEqual(arr1, arr2) == 0);
}

void test_areEqual_should_return_0_when_both_comparable_arrays_having_few_same_elements_but_different_length(){
	ArrayUtil arr1, arr2;
	int a1[] = {1,2,3};
	int a2[] = {1,2,3,4,5};

	arr1.length = 3;
	arr2.length = 5;

	arr1.typeSize = 4;
	arr2.typeSize = 4;


	arr1.base = a1;
	arr2.base = a2;

	assert(areEqual(arr1, arr2) == 0);
}


void test_areEqual_should_return_0_when_both_comparable_arrays_having_few_same_elements_but_different_typeSize(){
	ArrayUtil arr1, arr2;
	int a1[] = {1,2,3};
	int a2[] = {1,2,3};

	arr1.length = 3;
	arr2.length = 5;

	arr1.typeSize = 4;
	arr2.typeSize = 1;


	arr1.base = a1;
	arr2.base = a2;

	assert(areEqual(arr1, arr2) == 0);
}