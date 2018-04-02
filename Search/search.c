#include <stdio.h>

typedef int USER_TYPE;

int seqSearch(USER_TYPE *arrays, int arrayLen, USER_TYPE value, int comparaTo(USER_TYPE one, USER_TYPE two));
int binarySearch(USER_TYPE *arrays, int arrayLen, USER_TYPE value, int comparaTo(USER_TYPE one, USER_TYPE two));
void bubbleSortList(USER_TYPE *arrays, int arrayLen, int (*comparaTo)(USER_TYPE one, USER_TYPE two));
int comparaTo(USER_TYPE one, USER_TYPE two);
void printList(USER_TYPE *arrays, int len);

/*
 ����б�
 arrays:USER_TYPE���͵�����
 len:���鳤�� 
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
 �û�ʵ�ֵıȽϺ�������one>two������1�����ڷ���0��С�ڷ���-1�� 
 one��two:���Ƚϵ��� 
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
 ð������
  arrays:USER_TYPE������
  arrayLen:���鳤��
  comparaTo:�ȽϺ��� 
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
 ���ֲ��ң��ɹ�����ƥ���±� �����򷵻�-1.
  arrays:USER_TYPE������
  value:ƥ��Ԫ�� 
  arrayLen:���鳤��
  comparaTo:�ȽϺ��� 
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
 ˳����ң��ɹ�����ƥ���±� �����򷵻�-1.
  arrays:USER_TYPE������
  value:ƥ��Ԫ�� 
  arrayLen:���鳤��
  comparaTo:�ȽϺ��� 
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

	printf("δ����Ԫ��:");
	printList(arrays, 10);
	printf("%s", "�����ƥ��Ԫ��:");
	scanf("%d", &value);

	printf("(˳�����)ƥ��Ԫ���±꣺[%d]\n", seqSearch(arrays, 10, value, comparaTo));

	bubbleSortList(arrays, 10, comparaTo);
	printf("�����Ԫ��:");
	printList(arrays, 10);
	printf("(���ֲ���)ƥ��Ԫ���±꣺[%d]\n", binarySearch(arrays, 10, value, comparaTo));
	
	return 0;
}