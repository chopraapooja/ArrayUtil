#include <assert.h>
#include "arrayUtil.h"
#define CHAR_SIZE sizeof(char)
#define INT_SIZE sizeof(int)

typedef char* String; 
ArrayUtil util, resultUtil, expectedUtil;
int sample[] = {1,2,3,4,5};
//-----------------------------------------------Helper Functions --------------------------------
int isEven(void *hint, void *item){
	int *numberPtr = (int*)item;
	return *numberPtr % 2 ? 0 : 1;
}

int isDivisible(void *hint, void *item){
	int *numberPtr = (int*)item;
	int *hintPtr = (int*)hint;
	return *numberPtr % *hintPtr ? 0 : 1;
}

void increment(void* hint, void* sourceItem, void* destinationItem){
	int *hintPtr = (int*)hint;
	int *numberPtr = (int*)sourceItem;
	int *resultPtr = (int*)destinationItem;

	*resultPtr = *numberPtr + *hintPtr;
}

void toChar(void* hint, void* sourceItem, void* destinationItem){
	int *numberPtr = (int*)sourceItem;
	int *charPtr = (int*)destinationItem;
	*charPtr = *numberPtr;
}
//------------------------------------------------------------------------------------------------

void test_resize_sets_new_elements_to_zero_in_double(){
	double expectedArray[] = {1.0,0.0};
	ArrayUtil b = {expectedArray,sizeof(double),2};
	util = create(sizeof(double),1);
	((double*)util.base)[0] = 1.0;
	util = resize(util, 2);
	assert(areEqual(b, util));
}

void test_resize_sets_new_elements_to_NULL(){
	String expectedArray[] = {"digs",0};
	String name[] = {"digs"};

	ArrayUtil b = {expectedArray,sizeof(String),2};
	util = create(sizeof(String),1);

	memcpy(util.base, name, sizeof(String)*1);
	util = resize(util, 2);

	assert(areEqual(b, util));
};

void test_areEqual_should_return_1_when_both_comparable_arrays_are_same(){
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

void test_areEqual_should_return_0_when_both_comparable_arrays_are_not_same(){
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
	dispose(a);
}

void test_create_the_array_contents_will_all_be_set_to_zero(){
	ArrayUtil a = create(1,3);
	int i;
	for (i = 0; i < 3; ++i)
	{
		assert(((char*)a.base)[i] == 0);
	}
	dispose(a);
}

void test_resize_should_grow_length_of_array_and_set_them_to_zero_when_new_size_is_more(){
	ArrayUtil a = create(4,2);
	int i;
	a = resize(a,5);
	assert(a.length == 5);
	for (i = 0; i < 20; ++i)
	{
		assert(((char*)a.base)[i] == 0);
	}
	dispose(a);
}


void test_resize_should_shrink_length_of_array_when_new_size_is_less(){
	ArrayUtil a = create(1,5);
	int i;
	a = resize(a,3);
	assert(a.length == 3);
	free(a.base);
}

void test_resize_should_not_change_length_of_array_when_new_size_is_same_as_old_size(){
	ArrayUtil a = create(1,5);
	int i;
	a = resize(a,5);
	assert(a.length == 5);
	dispose(a);
}

void test_findFirst_on_providing_matchFunc_isEven_should_give_the_first_even_element_found_in_utilArray(){
	ArrayUtil array = create(sizeof(int),5);
	int arr[] = {1,2,3,4,5},*result;

	array.base = arr;
	result = (int*)findFirst(array,isEven,'\0');
	assert(*result == 2);
}


void test_findFirst_on_providing_matchFunc_isDivisble_with_3_should_give_the_first_element_found_tobe_divisble_by_3__in_utilArray(){
	ArrayUtil array = create(sizeof(int),5);
	int arr[] = {1,2,3,4,5},*result,divisor = 3;
	array.base = arr;
	result = (int*)findFirst(array,isDivisible,&divisor);
	assert(*result == 3);
}

void test_count_should_count_the_number_of_elements_matching_the_criteria(){
	ArrayUtil array = create(sizeof(int),5);
	int arr[] = {1,2,3,4,5},result;


	array.base = arr;
	result = count(array,isEven,'\0');
	assert(result == 2);		
}

void test_filter_should_filter_those_elements_which_are_matching_given_the_criteria(){
	ArrayUtil array = create(sizeof(int),5);
	int arr[] = {1,2,3,4,5},result,i,expected[] = {2,4};
	void *destination;
	array.base = arr;
	result = filter(array, isEven, null, &destination, 5);	
	for (i = 0; i < 2; ++i)
	{
		assert(((int*)destination)[i] == expected[i]);
	}
	assert(result == 2);
}

void test_map_should_map_source_to_destination_using_the_provided_convert_function(){
	int hint = 1, result[] = {2,3,4,5,6};
	
	util = (ArrayUtil){sample, sizeof(int), 5};
	resultUtil = create(util.typeSize, util.length);
	expectedUtil = (ArrayUtil){result, sizeof(int), 5};

	map(util, resultUtil, increment, &hint);
	
	assert(areEqual(expectedUtil, resultUtil));
	dispose(resultUtil);
}


void test_map_can_map_from_one_datatype_to_another(){
	int hint = 1, input[] = {97,98,99,100}; 
	char result[] = {'a','b','c','d'};
	
	util = (ArrayUtil){input, INT_SIZE, 4};
	resultUtil = create(CHAR_SIZE, util.length);
	expectedUtil = (ArrayUtil){result, CHAR_SIZE, util.length};

	map(util, resultUtil, toChar, &hint);
	
	assert(areEqual(expectedUtil, resultUtil));
	dispose(resultUtil);
}

void test_mapped_array_should_have_same_length_as_orignal_array(){
	int hint = 1, result[] = {2,3,4,5,6};
	
	util = (ArrayUtil){sample, sizeof(int), 5};
	resultUtil = create(util.typeSize, util.length);
	expectedUtil = (ArrayUtil){result, sizeof(int), 5};

	map(util, resultUtil, increment, &hint);
	
	assert(util.length == resultUtil.length);
	dispose(resultUtil);	
}