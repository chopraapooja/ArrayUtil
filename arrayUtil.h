struct ArrayUtil {
	void *base;
	int length;
	int typeSize;
};
typedef struct ArrayUtil ArrayUtil;
ArrayUtil create(int typeSize, int length);
int areEqual(ArrayUtil a, ArrayUtil b); 