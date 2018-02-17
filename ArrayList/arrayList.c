#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define NOT_FOUND -1

typedef unsigned char boolean;

/*
 ��ʾƽ���ϵĵ� 
*/ 
typedef struct Point {
	int row;
	int col;
} Point, USER_TYPE;

typedef struct Linear {
	int capacity;
	int count;
	USER_TYPE *arrays; 
} Linear;

boolean initLinearList(Linear **pLinear, int capacity); 					//��ʼ�����Ա�						
boolean destroyLinearList(Linear **pLinear);								//�������Ա� 
void iterator(Linear linear, void (*operatorValue)(USER_TYPE value)); 		//���б���е��� 
boolean resetLinearList(Linear *linear);									//�������Ա� 
int getLength(Linear linear);												//�õ����Ա��� 
boolean isEmpty(Linear linear);												//�п� 
boolean isFull(Linear linear);												//����
boolean append(Linear *linear, USER_TYPE value);							//׷�� 
boolean deleteElementByIndex(Linear *linear, int index);					//ɾ�� 
boolean getElementByIndex(Linear *linear, int index, USER_TYPE *value);		//�鿴 
boolean modifyElementByIndex(Linear *linear, int index, USER_TYPE value);	//�޸�
boolean insertElement(Linear *linear, int index, USER_TYPE value);			//���� 
int indexOf(Linear linear, USER_TYPE value, 								//�õ���һ��ƥ���Ԫ���±� 
	boolean (*equals)(USER_TYPE one, USER_TYPE two)); 		
void bubbleSortList(Linear *linear, boolean isAscending,    				//����                 	
	boolean (*oneGreaterThanTwo)(USER_TYPE one, USER_TYPE two));     	

void printOneElement(Point point);											//�û�ʵ�ֵĴ�ӡһ��Ԫ�� ���� 
boolean oneGreaterThanTwo(Point one, Point two);    						//�û�ʵ�ֵıȽϴ�С 	
boolean equals(Point one, Point two);										//�û�ʵ�ֵıȽ��Ƿ���� 

/*
 �û�ʵ�ֵĴ�ӡһ��Ԫ��
 point:������ 
*/
void printOneElement(Point point) {
	printf("(%d,%d)\n", point.row, point.col);
}

/*
 ���û�ʵ�ֵıȽϴ�С��������one > two������TRUE
 one:���Ƚ����� 
 two:���Ƚ����� 
*/  
boolean oneGreaterThanTwo(Point one, Point two) {
	if (((one.row*one.row + one.col*one.col) 
		- (two.row*two.row + two.col*two.col)) > 0) {
		return TRUE;
	}
	return FALSE;
}

/*
 �û�����ıȽ���Ⱥ��� 
 one:���Ƚ����� 
 two:���Ƚ����� 
*/
boolean equals(Point one, Point two) {
	if (one.row	== two.row && one.col == two.col) {
		return TRUE;
	}	
	return FALSE; 
}

/*
 ����ð������
 linear:ָ�����Ա��ָ��
 isAscending:�Ƿ�����TRUEΪ����FALSEΪ����
 oneGreaterThanTwo:�Ƚϴ�С���� 
*/
void bubbleSortList(Linear *linear, boolean isAscending,                    
	boolean (*oneGreaterThanTwo)(USER_TYPE one, USER_TYPE two)) {
	int i,j;
	boolean flag;
	USER_TYPE temp;
	
	for (i = 0; i < linear->count-1; i++) {
		for (j = 0; j < linear->count-i-1; j++) {
			flag = (TRUE == isAscending) ?
			oneGreaterThanTwo(linear->arrays[j], linear->arrays[j+1]) :
			oneGreaterThanTwo(linear->arrays[j+1], linear->arrays[j]);
			if (flag) {
				temp = linear->arrays[j];
				linear->arrays[j] = linear->arrays[j+1];
				linear->arrays[j+1] = temp;
			}
		}
	}		
} 

/*
 �õ�ƥ��ĵ�һ��Ԫ���±�
 linear:���Ա�ʵ��
 value:������Ԫ��
 equals���ȽϺ��� 
*/
int indexOf(Linear linear, USER_TYPE value, boolean (*equals)(USER_TYPE one, USER_TYPE two)) {
	int len = linear.count;
	
	while (linear.count > 0) {
		if (TRUE == equals(linear.arrays[len - linear.count--], value)) {
			return len - linear.count + 1;
		}
	}
	return NOT_FOUND;
}

/*
 ��ָ��λ�ò������� 
 linear:ָ�����Ա��ָ��
 index:����λ��
 value:�������� 
*/
boolean insertElement(Linear *linear, int index, USER_TYPE value) {
	int i; 
	
	if (linear == NULL || TRUE == isFull(*linear)
		|| index >= getLength(*linear) || index < 0) {
		return FALSE;
	}
	
	for (i = getLength(*linear); i > index; i--) {
		linear->arrays[i] = linear->arrays[i-1]; 
	}
	linear->arrays[index] = value;
	linear->count++;
	return TRUE;
} 

/*
 �޸�ָ��λ��Ԫ�� 
 linear:ָ�����Ա��ָ�� 
 index:�޸�λ��
 value:�޸ĵ�Ԫ�� 
*/
boolean modifyElementByIndex(Linear *linear, int index, USER_TYPE value) {
	if (linear == NULL || TRUE == isEmpty(*linear)
		|| index >= getLength(*linear) || index < 0) {
		return FALSE;
	}
	linear->arrays[index] = value;
	return TRUE;
}

/*
 �鿴ָ��λ��Ԫ��
 linear:ָ�����Ա��ָ�� 
 index:�鿴λ��
 value:���ص����� 
*/
boolean getElementByIndex(Linear *linear, int index, USER_TYPE *value) {
	if (linear == NULL || TRUE == isEmpty(*linear)
		|| index >= getLength(*linear) || index < 0) {
		return FALSE;
	}

	*value = linear->arrays[index];
	return TRUE;
} 

/*
 ɾ��ָ��λ��Ԫ��
 linear:ָ�����Ա��ָ�� 
 index:ɾ��Ԫ���±� 
*/
boolean deleteElementByIndex(Linear *linear, int index) {
	int i;
	if (linear == NULL || TRUE == isEmpty(*linear)
		|| index >= getLength(*linear) || index < 0) {
		return FALSE;
	}
	
	linear->count--;
	for (i = index; i < linear->count; i++) {
		linear->arrays[i] = linear->arrays[i+1];
	}
	return TRUE;
}

/*
 ׷��Ԫ��
 linear:ָ�����Ա��ָ�� 
 value:��׷��Ԫ��  
*/
boolean append(Linear *linear, USER_TYPE value) {
	if (linear == NULL || TRUE == isFull(*linear)) {
		return FALSE;
	}
	linear->arrays[linear->count++] = value;
	return TRUE;
}

/*
 ����
 linear:���Ա�ʵ�� 
*/
boolean isFull(Linear linear) {
	return linear.count == linear.capacity;
}

/*
 �п� 
 linear:���Ա�ʵ�� 
*/
boolean isEmpty(Linear linear) {
	return linear.count == 0;
}

/*
 �õ����Ա��� 
 linear:���Ա�ʵ�� 
*/
int getLength(Linear linear) {
	return linear.count;
}

/*
 �������Ա�
 linear:ָ�����Ա��ָ�� 
*/
boolean resetLinearList(Linear *linear) {
	if (linear == NULL) {
		return FALSE;
	}
	linear->count = 0;
	return TRUE;
}

/*
 �����Ա���е��� 
 linear:���Ա�ʵ��
 operatorValue:��Ԫ�ز����ĺ��� 
*/
void iterator(Linear linear, void (*operatorValue)(USER_TYPE value)) {
	int len = linear.count;
	
	while (linear.count > 0) {
		operatorValue(linear.arrays[len - linear.count--]);
	}
}

/*
 ���������ͷ����пռ�
 linear:ָ�����Ա�ָ��ĵ�ַ 
*/ 
boolean destroyLinearList(Linear **pLinear) {
	if (*pLinear == NULL) {
		return FALSE;
	}
	
	free((*pLinear)->arrays);
	free(*pLinear);
	*pLinear = NULL;
	return TRUE;
}

/*
 ��ʼ�����Ա� 
 linear:ָ�����Ա�ָ��ĵ�ַ
 capacity:����GREFFFDXC 
*/
boolean initLinearList(Linear **pLinear, int capacity) {
	if (*pLinear != NULL) {
		return FALSE;
	}
	
	*pLinear = (Linear*)malloc(sizeof(Linear));
	(*pLinear)->capacity = capacity;
	(*pLinear)->count = 0;
	(*pLinear)->arrays = (USER_TYPE*)malloc(sizeof(USER_TYPE)*capacity);
	return TRUE;
}

int main(void) {
	Linear *linear = NULL;
	int remainCapacity = 0;
	Point one = {
		1,
		1
	};
	
	initLinearList(&linear, 20);
	remainCapacity = 10 - getLength(*linear); 
	while (remainCapacity-- > 0) { 
		one.row = one.col= remainCapacity;						//������Ա� 
		append(linear, one);
	}
	append(linear, one);
	insertElement(linear, 0, one);
	//modifyElementByIndex(linear, 1, one);
	//bubbleSortList(linear, TRUE, oneGreaterThanTwo); 
	iterator(*linear, printOneElement);
	
	printf("��ǰ���Ա���:[%d]\n" , getLength(*linear));
	
	return 0;
}