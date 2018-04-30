#include <stdio.h>

#define SIZE 3

typedef int USER_TYPE;

void combination(USER_TYPE *arr, USER_TYPE *subArr, int start, int step, int len, void (*operatorArray)(USER_TYPE *arr, int len));
void printArrays(int *arr, int len);

void printArrays(int *arr, int len) {
	int i = 0;
	static int count = 1;
	
	printf("%d:(%d", count++, arr[i++]);
	for (i; i < len; i++) {
		printf(", %d", arr[i]);	
	}
	printf(")\n");
}

/*
 arr:ԭʼ����
 subArr:��ȡ����������洢�Ľ������ 
 start:�Ӽ�����ԭʼ���ϵ��±�
 step:��ȡstep�����
 len:ԭʼ���ϳ��� 
 operatorArray:����ϵĲ��� 
*/ 
void combination(USER_TYPE *arr, USER_TYPE *subArr, int start, int step, int len, void (*operatorArray)(USER_TYPE *arr, int len)) {
	int i;
	static int SUBLEN = 0;                 //����subArr�ĳ��� 
	
	if (step == 0) {
		operatorArray(subArr, SUBLEN);
		return;
	}

	for (i = start; i < len; i++) {
		if (i == 0) SUBLEN = step;
		subArr[SUBLEN-step] = arr[i];      //�������ϴ洢Ԫ�� 
		combination(arr, subArr, i+1, step-1, len, operatorArray);
	}
}

int main(void) {	
	int arr[] = {
		1, 2, 3, 4, 5, 6, 7, 8	
	};

	int subArr[SIZE] = {
		0
	};

	combination(arr, subArr, 0, SIZE, sizeof(arr)/sizeof(int), printArrays);	
	return 0;
}