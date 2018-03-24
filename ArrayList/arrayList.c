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

boolean initLinearList(Linear **pLinear, int capacity); 					//初始化线性表						
boolean destroyLinearList(Linear **pLinear);							//销毁线性表 
void iterator(Linear linear, void (*operatorValue)(USER_TYPE value)); 				//对列表进行迭代 
boolean resetLinearList(Linear *linear);							//重置线性表 
int getLength(Linear linear);									//得到线性表长度 
boolean isEmpty(Linear linear);									//判空 
boolean isFull(Linear linear);									//判满
boolean append(Linear *linear, USER_TYPE value);						//追加 
boolean deleteElementByIndex(Linear *linear, int index);					//删除 
boolean getElementByIndex(Linear *linear, int index, USER_TYPE *value);				//查看 
boolean modifyElementByIndex(Linear *linear, int index, USER_TYPE value);			//修改
boolean insertElement(Linear *linear, int index, USER_TYPE value);				//插入 
int indexOf(Linear linear, USER_TYPE value, 							//得到第一个匹配的元素下标 
	boolean (*equals)(USER_TYPE one, USER_TYPE two)); 		
void bubbleSortList(Linear *linear, boolean isAscending,    					//排序                 	
	boolean (*comparaTo)(USER_TYPE one, USER_TYPE two));     	

void printOneElement(Point point);								//用户实现的打印一个元素 函数 
boolean comparaTo(Point one, Point two);    						//用户实现的比较大小 	
boolean equals(Point one, Point two);								//用户实现的比较是否相等 

/*
 用户实现的打印一个元素
 point:点坐标 
*/
void printOneElement(Point point) {
	printf("(%d,%d)\n", point.row, point.col);
}

/*
 由用户实现的比较大小函数，若one > two，返回TRUE
 one:待比较数据 
 two:待比较数据 
*/  
boolean comparaTo(Point one, Point two) {
	if (((one.row*one.row + one.col*one.col) 
		- (two.row*two.row + two.col*two.col)) > 0) {
		return TRUE;
	}
	return FALSE;
}

/*
 用户定义的比较相等函数 
 one:待比较数据 
 two:待比较数据 
*/
boolean equals(Point one, Point two) {
	if (one.row	== two.row && one.col == two.col) {
		return TRUE;
	}	
	return FALSE; 
}

/*
 进行冒泡排序
 linear:指向线性表的指针
 isAscending:是否升序。TRUE为升序，FALSE为降序
 comparaTo:比较大小函数 
*/
void bubbleSortList(Linear *linear, boolean isAscending,                    
	boolean (*comparaTo)(USER_TYPE one, USER_TYPE two)) {
	int i,j;
	boolean flag;
	USER_TYPE temp;
	
	for (i = 0; i < linear->count-1; i++) {
		for (j = 0; j < linear->count-i-1; j++) {
			flag = (TRUE == isAscending) ?
			comparaTo(linear->arrays[j], linear->arrays[j+1]) :
			comparaTo(linear->arrays[j+1], linear->arrays[j]);
			if (flag) {
				temp = linear->arrays[j];
				linear->arrays[j] = linear->arrays[j+1];
				linear->arrays[j+1] = temp;
			}
		}
	}		
} 

/*
 得到匹配的第一个元素下标
 linear:线性表实例
 value:待查找元素
 equals：比较函数 
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
 向指定位置插入数据 
 linear:指向线性表的指针
 index:插入位置
 value:插入数据 
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
 修改指定位置元素 
 linear:指向线性表的指针 
 index:修改位置
 value:修改的元素 
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
 查看指定位置元素
 linear:指向线性表的指针 
 index:查看位置
 value:返回的数据 
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
 删除指定位置元素
 linear:指向线性表的指针 
 index:删除元素下标 
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
 追加元素
 linear:指向线性表的指针 
 value:待追加元素  
*/
boolean append(Linear *linear, USER_TYPE value) {
	if (linear == NULL || TRUE == isFull(*linear)) {
		return FALSE;
	}
	linear->arrays[linear->count++] = value;
	return TRUE;
}

/*
 判满
 linear:线性表实例 
*/
boolean isFull(Linear linear) {
	return linear.count == linear.capacity;
}

/*
 判空 
 linear:线性表实例 
*/
boolean isEmpty(Linear linear) {
	return linear.count == 0;
}

/*
 得到线性表长度 
 linear:线性表实例 
*/
int getLength(Linear linear) {
	return linear.count;
}

/*
 重置线性表
 linear:指向线性表的指针 
*/
boolean resetLinearList(Linear *linear) {
	if (linear == NULL) {
		return FALSE;
	}
	linear->count = 0;
	return TRUE;
}

/*
 对线性表进行迭代 
 linear:线性表实例
 operatorValue:对元素操作的函数 
*/
void iterator(Linear linear, void (*operatorValue)(USER_TYPE value)) {
	int len = linear.count;
	
	while (linear.count > 0) {
		operatorValue(linear.arrays[len - linear.count--]);
	}
}

/*
 销毁链表，释放所有空间
 linear:指向线性表指针的地址 
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
 初始化线性表 
 linear:指向线性表指针的地址
 capacity:容量
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
		one.row = one.col= remainCapacity;						//填充线性表 
		append(linear, one);
	}
	append(linear, one);
	insertElement(linear, 0, one);
	//modifyElementByIndex(linear, 1, one);
	//bubbleSortList(linear, TRUE, comparaTo); 
	iterator(*linear, printOneElement);
	
	printf("current linear length:[%d]\n" , getLength(*linear));
	
	return 0;
}
