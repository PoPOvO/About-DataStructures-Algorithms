#include <stdio.h>

typedef int USER_TYPE;

int search(USER_TYPE *arrays, int arrayLen, USER_TYPE value, int comparaTo(USER_TYPE one, USER_TYPE two));
void bubbleSortList(USER_TYPE *arrays, int arrayLen, int (*comparaTo)(USER_TYPE one, USER_TYPE two));
int comparaTo(USER_TYPE one, USER_TYPE two);
void printList(USER_TYPE *arrays, int len);

void printList(USER_TYPE *arrays, int len) {
	int i = 0;
	
	printf("[");
	while (i < len) {
		printf(" %d ", arrays[i++]);
	}
	printf("]\n");
}

int comparaTo(USER_TYPE one, USER_TYPE two) {
	if (one > two) {
		return 1;
	} else if (one < two) {
		return -1;
	}
	return 0;
}

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

int search(USER_TYPE *arrays, int arrayLen, USER_TYPE value, int comparaTo(USER_TYPE one, USER_TYPE two)) {
	int head = 0;
	int tail = arrayLen-1;
	int middle = (head + tail) / 2;

	while (head <= tail) {
		if (0 == comparaTo(arrays[middle], value)) {
			return middle;
		} else if (1 == comparaTo(arrays[middle], value)) {
			tail = middle-1;
			middle = (head + tail) / 2;
		} else if (-1 == comparaTo(arrays[middle], value)) {
			head = middle+1;
			middle = (head + tail) / 2;
		}
	}
	return -1;
}

int main(void) {
	USER_TYPE value;
	USER_TYPE arrays[10] = {
		8, 9, 7, 6, 5, 4, 3, 2, 1, 0	
	};

	bubbleSortList(arrays, 10, comparaTo);
	printf("ÅÅÐòºóÔªËØ:");
	printList(arrays, 10);
	
	printf("%s", "ÊäÈë´ýÆ¥ÅäÔªËØ:");
	scanf("%d", &value);
	printf("Æ¥ÅäÔªËØÏÂ±ê£º[%d]\n", search(arrays, 10, value, comparaTo));
	
	return 0;
}