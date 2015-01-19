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

void test_create_should_set_the_length_and_typeSize_fields_of_array_to_the_values_passed_to_create_function(){
	ArrayUtil a = create(1,3);
	assert(a.length == 3);
	assert(a.typeSize == 1);
}

void test_create_the_array_contents_will_all_be_set_to_zero(){
	ArrayUtil a = create(1,3);
	int i;
	for (i = 0; i < 3; ++i)
	{
		assert(((char*)a.base)[i] == 0);
	}
}

// void test_create(){
// 	ArrayUtil intArray, charArray, floatArray, customArray;
// 	int i;
// 	intArray = create(sizeof(int), 5);
// 	charArray = create(sizeof(char), 5);
// 	floatArray = create(sizeof(float), 5);
// 	customArray = create(8, 5);

// 	int intArr[] = {1,2,3,4,5};
// 	float floatArr[] = {1.5,2.5,3.5,4.5,5.5};
// 	char charArr[] = {'a','b','c','d','e'};
// 	char *strings[] = {"Bananana","Bananana","Bananana","Bananana","Bananana"};

// 	intArray.base = (void*)intArr;
// 	charArray.base = (void*)charArr;
// 	floatArray.base = (void*)floatArr;
// 	customArray.base = (void*)strings;
// }



