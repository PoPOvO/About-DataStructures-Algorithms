#include<stdio.h>
#include<malloc.h>

#ifndef USER_TYPE
	typedef int USER_TYPE;
#endif

#define FALSE	0
#define TRUE	1 

typedef unsigned char boolean;

typedef struct {
	int row;
	int col;
	USER_TYPE *matrix; 
}MATRIX;

boolean creatArray(MATRIX **arr, int row, int col);
void destroyArray(MATRIX **arr);
boolean getElement(MATRIX arr, int row, int col, USER_TYPE *value);
boolean setElement(MATRIX* arr, int row, int col, USER_TYPE value); 

boolean setElement(MATRIX* arr, int row, int col, USER_TYPE value) {
	if(row < 0 || row > arr->row || col < 0 || col > arr->col) {
		return FALSE;
	}
	arr->matrix[row*(arr->col + col)] = value;
	return TRUE;
}

boolean getElement(MATRIX arr, int row, int col, USER_TYPE *value) {
	if(row < 0 || row > arr.row || col < 0 || col > arr.col) {
		return FALSE;
	}

	*value = arr.matrix[row*(arr.col) + col];
	return TRUE;
}

void destroyArray(MATRIX **arr) {	
	free((*arr)->matrix);
	free(*arr);
	*arr = NULL;
}

boolean creatArray(MATRIX **arr, int row, int col) {
	MATRIX *temp = NULL;
	
	if(*arr != NULL) {
		return FALSE;			
	}
	temp = (MATRIX *)calloc(sizeof(MATRIX), 1);
	
	if(temp == NULL) {
		return FALSE;
	}
	temp->matrix = (USER_TYPE *)calloc(sizeof(USER_TYPE), row*col);
	
	if((temp->matrix) == NULL) {
		free(temp);
		return FALSE;
	} 
	temp->row = row;
	temp->col = col;
	*arr = temp;

	return TRUE;
}

int main(void) {
	MATRIX *arr = NULL;
	int row;
	int col;
	int count = 0; 
	USER_TYPE value;
	char ch;
	
	printf("��������������������:");
	scanf("%d%d", &row, &col); 
	creatArray(&arr, row, col);
	printf("��������Ԫ��:(˳���������������A������ĳһ����Ԫ��������B)");
	
	if('A' == (ch = getchar())) {
		while(count < row*col) {
		printf("�����������Ԫ�أ�\n(%d/%d):", ++count, row*col); 
		scanf("%d", &value); 
		arr->matrix[count-1] = value;
		}
	} 
	else if('B' == (ch = getchar())) {
		printf("�������ֹԪ�ص����У�");
		scanf("%d%d", &row, &col);
		printf("��������ֵ:"); 
		scanf("%d", &value); 
		setElement(arr, row-1, col-1, value);	
	}
	
	printf("��������Ҫ�鿴����������:");
	scanf("%d%d", &row, &col);
	getElement(*arr, row-1, col-1, &value);
	printf("%d\n", value);	 
	destroyArray(&arr);
	return 0;
}