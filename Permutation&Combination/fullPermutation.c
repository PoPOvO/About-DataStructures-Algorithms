#include <stdio.h>

typedef int USER_TYPE;

void swap(USER_TYPE *p, USER_TYPE *q);
void fullPermutation(USER_TYPE *arr, int start, int len, void (*operatorArray)(USER_TYPE *arr, int len));
void printArrays(int *arr, int len);

void printArrays(int *arr, int len) {
	int i = 0;
	static int count = 1;
	
	printf("%d:(%d", count++, arr[i++]);
	for (i; i < len; i++)
		printf(", %d", arr[i]);
	printf(")\n");
}

/*
 arr:原始集合
 start:子集合在原始集合的其实下标
 len:原始集合长度
 operatorArray:对集合操作的函数 
*/ 
void fullPermutation(USER_TYPE *arr, int start, int len, void (*operatorArray)(USER_TYPE *arr, int len)) {
	int i = start;
	
	if (start == len-1) {            //无子集时返回 
		operatorArray(arr, len);
		return;	
	}
	
	for (i = start; i < len; i++) {
		swap(&arr[start], &arr[i]);
		fullPermutation(arr, start + 1, len, operatorArray);
		swap(&arr[i], &arr[start]);
	}
}

void swap(USER_TYPE *p, USER_TYPE *q) {
	USER_TYPE t;
	t = *p;
	*p = *q;
	*q = t;
}

int main(void) {	
	int arr[] = {
		1, 2, 3, 4	
	};
	
	fullPermutation(arr, 0, 4, printArrays);

	return 0;
}