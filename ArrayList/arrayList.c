#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define NOT_FOUND -1

typedef unsigned char boolean;

/*
 表示平面上的点 
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

boolean initLinearList(Linear **pLinear, int capacity); 
boolean destroyLinearList(Linear **pLinear);
void iterator(Linear linear, void (*operatorValue)(USER_TYPE value)); 
void printOneElement(Point point);
boolean resetLinearList(Linear *linear);
int getLength(Linear linear);
boolean isEmpty(Linear linear);
boolean isFull(Linear linear);
boolean append(Linear *linear, USER_TYPE value);
boolean deleteElementByIndex(Linear *linear, int index);
boolean getElementByIndex(Linear *linear, int index, USER_TYPE *value);
boolean modifyElementByIndex(Linear *linear, int index, USER_TYPE value);
boolean insertElement(Linear *linear, int index, USER_TYPE value);
int indexOf(Linear linear, USER_TYPE value, boolean (*equals)(USER_TYPE one, USER_TYPE two)); 
void bubbleSortList(Linear *linear, boolean isAscending,                     	
	boolean (*oneGreaterThanTwo)(USER_TYPE one, USER_TYPE two));     
boolean oneGreaterThanTwo(Point one, Point two);    

boolean oneGreaterThanTwo(Point one, Point two) {
	if (((one.row*one.row + one.col*one.col) 
		- (two.row*two.row + two.col*two.col)) > 0) {
		return TRUE;
	}
	return FALSE;
}

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

int indexOf(Linear linear, USER_TYPE value, boolean (*equals)(USER_TYPE one, USER_TYPE two)) {
	int len = linear.count;
	
	while (linear.count > 0) {
		if (TRUE == equals(linear.arrays[len - linear.count--], value)) {
			return len - linear.count + 1;
		}
	}
	return NOT_FOUND;
}

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

boolean modifyElementByIndex(Linear *linear, int index, USER_TYPE value) {
	if (linear == NULL || TRUE == isEmpty(*linear)
		|| index >= getLength(*linear) || index < 0) {
		return FALSE;
	}
	linear->arrays[index] = value;
	return TRUE;
}

boolean getElementByIndex(Linear *linear, int index, USER_TYPE *value) {
	if (linear == NULL || TRUE == isEmpty(*linear)
		|| index >= getLength(*linear) || index < 0) {
		return FALSE;
	}

	*value = linear->arrays[index];
	return TRUE;
} 

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

boolean append(Linear *linear, USER_TYPE value) {
	if (linear == NULL || TRUE == isFull(*linear)) {
		return FALSE;
	}
	linear->arrays[linear->count++] = value;
	return TRUE;
}

boolean isFull(Linear linear) {
	return linear.count == linear.capacity;
}

boolean isEmpty(Linear linear) {
	return linear.count == 0;
}

int getLength(Linear linear) {
	return linear.count;
}

boolean resetLinearList(Linear *linear) {
	if (linear == NULL) {
		return FALSE;
	}
	linear->count = 0;
	return TRUE;
}

void printOneElement(Point point) {
	printf("(%d,%d)\n", point.row, point.col);
}

void iterator(Linear linear, void (*operatorValue)(USER_TYPE value)) {
	int len = linear.capacity;
	
	while (linear.capacity > 0) {
		operatorValue(linear.arrays[len - linear.capacity--]);
	}
}

boolean destroyLinearList(Linear **pLinear) {
	if (*pLinear == NULL) {
		return FALSE;
	}
	
	free((*pLinear)->arrays);
	free(*pLinear);
	*pLinear = NULL;
	return TRUE;
}

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
	
	initLinearList(&linear, 10);
	remainCapacity = 10 - getLength(*linear); 
	while (remainCapacity-- > 0) { 					//填充线性表 
		append(linear, one);
	}
	iterator(*linear, printOneElement);
	
	printf("当前线性表长度:[%d]\n" , getLength(*linear));
	
	return 0;
}