#include <assert.h>
#include "arrayUtil.h"
typedef char* String; 
typedef struct student student; 

ArrayUtil util;

struct student
{
	char *name;
	int age;
	float marks;
};

// void test_create_Structures_with_all_fields_NULL(){
// 	student temp = {"",0,0.0};
// 	student Student[1] = {temp};
// 	ArrayUtil expected = {Student,sizeof(student),1};
// 	util = create(sizeof(student),1);
// 	assert(areEqual(expected,util));
// };

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

	int isEven(void *hint, void *item){
		int *numberPtr = (int*)item;
		return *numberPtr % 2 ? 0 : 1;
	}
	array.base = arr;
	result = (int*)findFirst(array,isEven,'\0');
	assert(*result == 2);
}


void test_findFirst_on_providing_matchFunc_isDivisble_with_3_should_give_the_first_element_found_tobe_divisble_by_3__in_utilArray(){
	ArrayUtil array = create(sizeof(int),5);
	int arr[] = {1,2,3,4,5},*result,divisor = 3;

	int isDivisible(void *hint, void *item){
		int *numberPtr = (int*)item;
		int *hintPtr = (int*)hint;
		return *numberPtr % *hintPtr ? 0 : 1;
	}
	array.base = arr;
	result = (int*)findFirst(array,isDivisible,&divisor);
	assert(*result == 3);
}

void test_count_should_count_the_number_of_elements_matching_the_criteria(){
	ArrayUtil array = create(sizeof(int),5);
	int arr[] = {1,2,3,4,5},result;

	int isEven(void *hint, void *item){
		int *numberPtr = (int*)item;
		return *numberPtr % 2 ? 0 : 1;
	}
	array.base = arr;
	result = count(array,isEven,'\0');
	assert(result == 2);		
}

void test_filter_should_filter_the_number_of_elements_matching_the_criteria(){
	ArrayUtil array = create(sizeof(int),5);
	int arr[] = {1,2,3,4,5},result,i,expected[] = {2,4};
	void *destination;
	int isEven(void *hint, void *item){
		int *numberPtr = (int*)item;
		return *numberPtr % 2 ? 0 : 1;
	}
	array.base = arr;
	result = filter(array, isEven, null, &destination, 5);	
	for (i = 0; i < 2; ++i)
	{
		assert(((int*)destination)[i] == expected[i]);
	}
	assert(result == 2);
}

