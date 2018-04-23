#include <stdio.h>

typedef int USER_TYPE;

void swap(USER_TYPE *p, USER_TYPE *q);
void fullPermutation(USER_TYPE *arr, int start, int len, void (*operatorArray)(USER_TYPE *arr, int len));
void printArrays(int *arr, int len);

void printArrays(int *arr, int len) {
	int i = 0;
	
	printf("(%d", arr[i++]);
	for (i; i < len; i++)
		printf(", %d", arr[i]);
	printf(")\n");
}

void fullPermutation(USER_TYPE *arr, int start, int len, void (*operatorArray)(USER_TYPE *arr, int len)) {
	int i = start;
	
	if (start == len) {
		operatorArray(arr, len);	
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
		1, 2, 3	
	};
	
	fullPermutation(arr, 0, 3, printArrays);
	
	return 0;
}