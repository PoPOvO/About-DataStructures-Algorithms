#include <stdio.h>

typedef int USER_TYPE;

int seqSearch(USER_TYPE *arrays, int arrayLen, USER_TYPE value, int comparaTo(USER_TYPE one, USER_TYPE two));
int binarySearch(USER_TYPE *arrays, int arrayLen, USER_TYPE value, int comparaTo(USER_TYPE one, USER_TYPE two));
void bubbleSortList(USER_TYPE *arrays, int arrayLen, int (*comparaTo)(USER_TYPE one, USER_TYPE two));
int comparaTo(USER_TYPE one, USER_TYPE two);
void printList(USER_TYPE *arrays, int len);

/*
 输出列表
 arrays:USER_TYPE类型的数组
 len:数组长度 
*/
void printList(USER_TYPE *arrays, int len) {
	int i = 0;
	
	printf("[");
	while (i < len) {
		printf(" %d ", arrays[i++]);
	}
	printf("]\n");
}

/*
 用户实现的比较函数。若one>two，返回1，等于返回0，小于返回-1。 
 one、two:待比较的量 
*/
int comparaTo(USER_TYPE one, USER_TYPE two) {
	if (one > two) {
		return 1;
	} else if (one < two) {
		return -1;
	}
	return 0;
}

/*
 冒泡升序
  arrays:USER_TYPE的数组
  arrayLen:数组长度
  comparaTo:比较函数 
*/
void bubbleSortList(USER_TYPE *arrays, int arrayLen, int (*comparaTo)(USER_TYPE one, USER_TYPE two)) {
	int i,j;
	USER_TYPE temp;
	
	for (i = 0; i < arrayLen-1; i++) {
		for (j = 0; j < arrayLen-i-1; j++) {
			if (1 == comparaTo(arrays[j], arrays[j+1])) {
				temp = arrays[j];
				arrays[j] = arrays[j+1];
				arrays[j+1] = temp;
			}
		}
	}
}

/*
 二分查找，成功返回匹配下标 ，否则返回-1.
  arrays:USER_TYPE的数组
  value:匹配元素 
  arrayLen:数组长度
  comparaTo:比较函数 
*/
int binarySearch(USER_TYPE *arrays, int arrayLen, USER_TYPE value, int comparaTo(USER_TYPE one, USER_TYPE two)) {
	int head = 0;
	int tail = arrayLen-1;
	int middle = (head + tail) / 2;

	while (head <= tail) {
		if (0 == comparaTo(arrays[middle], value)) {
			return middle;
		} else if (1 == comparaTo(arrays[middle], value)) {
			tail = middle-1;
		} else { 
			head = middle+1; 
		}
		middle = (head + tail) / 2;
	}
	return -1;
}

/*
 顺序查找，成功返回匹配下标 ，否则返回-1.
  arrays:USER_TYPE的数组
  value:匹配元素 
  arrayLen:数组长度
  comparaTo:比较函数 
*/
int seqSearch(USER_TYPE *arrays, int arrayLen, USER_TYPE value, int comparaTo(USER_TYPE one, USER_TYPE two)) {
	while (arrayLen-- >= 0) { 
		if (comparaTo(arrays[arrayLen], value) == 0) {
			return arrayLen;
		}
	}
	return -1;
}

int main(void) {
	USER_TYPE value;
	USER_TYPE arrays[10] = {
		8, 9, 7, 6, 5, 4, 3, 2, 1, 0	
	};

	printf("未排序元素:");
	printList(arrays, 10);
	printf("%s", "输入待匹配元素:");
	scanf("%d", &value);

	printf("(顺序查找)匹配元素下标：[%d]\n", seqSearch(arrays, 10, value, comparaTo));

	bubbleSortList(arrays, 10, comparaTo);
	printf("排序后元素:");
	printList(arrays, 10);
	printf("(二分查找)匹配元素下标：[%d]\n", binarySearch(arrays, 10, value, comparaTo));
	
	return 0;
}