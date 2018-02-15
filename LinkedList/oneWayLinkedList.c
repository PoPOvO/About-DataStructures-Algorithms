/*
 不带头节点单向链表,每个节点存储用户输入的点坐标 
*/
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

typedef struct Node {
	USER_TYPE value;
	struct Node* next;
} Node, *LinkedList;

boolean initLinkedList(Node **pHead, boolean (*inputValue)(USER_TYPE*)); //初始化链表 
boolean destoryLinkedList(Node **pHead);                                 //销毁链表 
void printLinkedList(Node *head);										 //打印链表 
boolean appendValue(Node* head, USER_TYPE value);                        //追加 
boolean insertNode(Node **pHead, USER_TYPE value, int pos);         	 //插入 
boolean deleteNodeByIndex(Node **pHead, int pos);                        //删除节点 
boolean getValueByIndex(Node *head, USER_TYPE *value, int index);        //查看节点数据 
boolean modifyNodeByIndex(Node *head, USER_TYPE value, int index);       //修改节点数据 
int getLength(Node *head);                                               //获取链表长度 
int indexOf(Node *head, USER_TYPE value, 								 //得到第一个匹配元素的下标 
	boolean (*equals)(USER_TYPE one, USER_TYPE two)); 
void bubbleSortList(Node *head, boolean isAscending,                     //排序 
	boolean (*oneGreaterThanTwo)(USER_TYPE one, USER_TYPE two));     
boolean iterator(Node *head, void (*operatorValue)(USER_TYPE value));    //对链表进行迭代 

boolean oneGreaterThanTwo(Point one, Point two);                         //用户实现的比较大小函数 
boolean equals(Point one, Point two);									 //用户定义的比较相等函数
boolean inputPoint(Point *point);										 //用户实现的输入函数 

/*
 由用户实现的输入函数，用于读入一个值 。 
 *point:一个点坐标数据 
*/ 
boolean inputPoint(Point *point) {
	printf("输入点坐标(ctrl+Z结束):");
	return 2 == scanf("%d%d", &(point->row), &(point->col)); 
}

/*
 由用户实现的比较大小函数，若one > two，返回TRUE
 one:待比较数据 
 two:待比较数据 
*/ 
boolean oneGreaterThanTwo(Point one, Point two) {
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
 对链表进行遍历
 head:链表头节点地址 
 operatorValue：由用户实现，对链表元素进行操作 
*/
boolean iterator(Node *head, void (*operatorValue)(USER_TYPE value)) {
	if (head == NULL) {
		return FALSE;
	}
	
	while (head != NULL) {
		operatorValue(head->value);		
		head = head->next;
	}
	return TRUE;
} 

/*
 使用冒泡排序对链表进行排序
 head:链表头节点地址 
 isAscending:是否采用升序，升序 为TRUE，降序为FALSE 
 oneGreaterThanTwo:由用户实现的比较函数 
*/ 
void bubbleSortList(Node *head, boolean isAscending,
	boolean (*oneGreaterThanTwo)(USER_TYPE one, USER_TYPE two) ) {
	
	Node *ptr;
	int listLen = getLength(head);
	int i,j;
	USER_TYPE temp;
	boolean flag;
	
	for (i = 0; i < listLen-1; i++) {
		ptr = head; 			//需要保存头指针 
		for (j = 0; j < listLen-i-1; j++) {
			//升序或者降序 
			isAscending == TRUE ? 
				(flag = oneGreaterThanTwo(ptr->value, ptr->next->value)) :
				(flag = oneGreaterThanTwo(ptr->next->value, ptr->value));
			if (flag) {
				temp = ptr->value;
				ptr->value = ptr->next->value;
				ptr->next->value = temp;
			}
			ptr = ptr->next;
		}
	}
}

/*
 得到第一个和所给元素相等的元素下标 
 head:链表头结点地址  
 value:目标元素
 equals:用户定义的比较函数 
*/
int indexOf(Node *head, USER_TYPE value, boolean (*equals)(USER_TYPE one, USER_TYPE two)) {
	int cnt = NOT_FOUND;
	while (head != NULL) {
		++cnt;
		if (TRUE == equals(head->value, value)) {
			return cnt;
		}
		head = head->next;
	}
	return cnt;
}

/*
 得到链表长度
 head:链表头结点地址  
*/
int getLength(Node *head) {
	int cnt = 0;
	
	while (head != NULL) {
		cnt++;
		head = head->next;	
	}
	return cnt;
}

/*
 根据下标修改节点数据域
 head:链表头结点地址 
 value:修改的数据 
 index:节点下标  
*/
boolean modifyNodeByIndex(Node *head, USER_TYPE value, int index) {
	Node *ptr = head;
	
	if (head == NULL || index < 0 || index > getLength(head)-1) {
		return FALSE;
	}
	
	while (head != NULL) {
		if (index-- == 0) {
			head->value = value;
			return TRUE;
		}
		head = head->next;
	}
	return FALSE;
}

/*
 根据下标得到对应节点数据域 
 head:链表头结点地址 
 value:数据域通过指针返回
 index:节点下标 
*/ 
boolean getValueByIndex(Node *head, USER_TYPE *value, int index) {
	while (head != NULL) {
		if (index-- == 0) {
			*value = head->value;
			return TRUE;
		}
		head = head->next;
	}
	return FALSE;
}

/*
 在指定位置删除一个节点，可以为头节点 
 pHead:指向头节点的指针的地址 
 pos:删除节点下标 
*/ 
boolean deleteNodeByIndex(Node **pHead, int pos) {	
	Node *prev;
	Node *temp = *pHead;
	int len = getLength(*pHead); 
	if (pos < 0 || pos > len-1 || *pHead == NULL) {
		return FALSE;
	}

	//删除头节点 
	if (pos == 0) {
		prev = *pHead;
		*pHead = (*pHead)->next;
		free(prev);
		prev = NULL;
		return TRUE;
	}
	
	while (temp != NULL) {
		if (pos-- == 0) {
			prev->next = temp->next;
			free(temp);	
			return TRUE;				
		}
		prev = temp;
		temp = temp->next;
	}
	return FALSE;
}

/*
 在指定位置插入一个节点
 head:链表头结点地址 
 value:插入节点的数据域 
 pos:插入位置 
*/
boolean insertNode(Node **pHead, USER_TYPE value, int pos) {
	Node *temp = *pHead;
	Node *current;
	if (pos < 0) {
		return FALSE;
	}

	if (pos == 0) {
		current = (Node*)malloc(sizeof(Node));
		current->value = value;
		current->next = *pHead;
		*pHead = current; 
		return TRUE;
	}

	while (temp != NULL) {
		if (pos-- == 1) {
			current = (Node*)malloc(sizeof(Node));
			current->value = value;
			current->next = temp->next;
			temp->next = current;
			return TRUE;
		} 
		temp = temp->next;
	}
	return FALSE;	
}

/*
 追加元素
 head:链表头结点地址   
 value:追加数据 
*/
boolean appendValue(Node* head, USER_TYPE value) {
	Node *prev;
	if (head == NULL) {
		return FALSE;
	}
	
	while (head != NULL) {
		prev = head;
		head = head->next;
	}
	
	head = (Node*)malloc(sizeof(Node));
	head->value = value;
	head->next = NULL;
	prev->next = head;
	return TRUE;
} 

/*
 打印链表元素到控制台
 head:链表头结点地址 
*/
void printLinkedList(Node *head) {
	puts("结果如下：");
	while (head != NULL) {
		printf("(%d,%d) ", head->value.row, head->value.col);
		head = head->next;
	}
}

/*
 销毁链表，释放所有节点。
 pHead:指向头节点的指针的地址 
*/ 
boolean destoryLinkedList(Node **pHead) {
	Node *temp = NULL;
	
	if (*pHead == NULL) {
		return FALSE;
	}
	
	while (*pHead != NULL) {
		temp = (*pHead)->next;
		free(*pHead);
		*pHead = temp;
	}
	*pHead = NULL;
	return TRUE;
}

/*
 初始化链表。 
 pHead:链表头节点地址 
 inputValue：需要由用户实现的函数。用于读入一个值。 
*/ 
boolean initLinkedList(Node **pHead, boolean (*inputValue)(USER_TYPE*)) {
	Node *current = NULL;
	Node *prev = NULL;
	USER_TYPE value;
	
	if (*pHead != NULL) {
		return FALSE;
	}
	
	while (TRUE == inputValue(&value)) {
		current = (Node*)malloc(sizeof(Node));
		current->value = value;
		current->next = NULL;
		
		if (*pHead == NULL) {
			*pHead = prev = current;
		} else {
			prev->next = current;
			prev = current;
		}
	}
	return TRUE;
}

/*
1 2 3 4 5 6 7 8
*/
int main(void) {
	LinkedList head = NULL;
	Point temp = {
		0,
		0	
	};
	
 	initLinkedList(&head, inputPoint);
 	modifyNodeByIndex(head, temp, 3);
	//appendValue(head, temp);
	insertNode(&head, temp, 2);
	bubbleSortList(head, FALSE, oneGreaterThanTwo); 
	printLinkedList(head);
	printf("\nIndex:%d", indexOf(head, temp, equals));
 	destoryLinkedList(&head);
	return 0;
}