struct ArrayUtil {
	void *base;
	int length;
	int typeSize;
};
typedef struct ArrayUtil ArrayUtil;
ArrayUtil create(int typeSize, int length);
int areEqual(ArrayUtil a, ArrayUtil b); 
ArrayUtil resize(ArrayUtil array, int length);
void dispose(ArrayUtil util);