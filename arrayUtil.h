struct ArrayUtil {
	void *base;
	int typeSize;
	int length;
};
#define null '\0'
typedef struct ArrayUtil ArrayUtil;
typedef int MatchFunc(void *hint, void *item);

ArrayUtil create(int typeSize, int length);
int areEqual(ArrayUtil a, ArrayUtil b); 
ArrayUtil resize(ArrayUtil array, int length);
void dispose(ArrayUtil util);
void* findFirst(ArrayUtil util, MatchFunc* match, void* hint);
int count(ArrayUtil util, MatchFunc* match, void* hint);
int filter(ArrayUtil util, MatchFunc* match, void* hint, void** destination, int maxItems );