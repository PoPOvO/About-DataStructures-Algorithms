#include <stdio.h> 
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/*
* 单向链表,每个节点存储用户输入的点坐标 
*/
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

/*
 初始化链表。 
 pHead:链表头节点地址 
 inputValue：需要由用户实现的函数。用于读入一个值。 
*/ 
boolean initLinkedList(Node **pHead, boolean (*inputValue)(USER_TYPE*));

/*
 由用户实现的函数，用于读入一个值 。 
 *point:一个点坐标数据 
*/ 
boolean inputPoint(Point *point);

/*
 销毁链表，释放所有节点。
 pHead:指向头节点的指针的地址 
*/ 
boolean destoryLinkedList(Node **pHead);

/*
 打印链表元素到控制台
 head:链表头结点地址 
*/
void printLinkedList(Node *head);

/*
 追加元素
 head:链表头结点地址   
 value:追加数据 
*/
boolean appendValue(Node* head, USER_TYPE value); 

/*
 在指定位置后插一个节点
 head:链表头结点地址 
 value:插入节点的数据域 
 pos:插入位置 
*/
boolean behindInsertNode(Node *head, USER_TYPE value, int pos);

/*
 在指定位置前插一个节点
 head:链表头结点地址 
 value:插入节点的数据域 
 pos:插入位置 
*/
boolean frontInsertNode(Node **pHead, USER_TYPE value, int pos);

/*
 在指定位置删除一个节点，可以为头节点 
 pHead:指向头节点的指针的地址 
 pos:删除节点下标 
*/ 
boolean deleteNode(Node **pHead, int pos);

/*
 根据下标得到对应节点数据域 
 head:链表头结点地址 
 value:数据域通过指针返回
 index:节点下标 
*/ 
boolean getValueByIndex(Node *head, USER_TYPE *value, int index);

/*
 根据下标修改节点数据域
 head:链表头结点地址 
 value:修改的数据 
 index:节点下标  
*/
boolean motifyNodeByIndex(Node *head, USER_TYPE value, int index);

/*
 得到链表长度
 head:链表头结点地址  
*/
int getLength(Node *head);

/*
 使用冒泡排序对链表进行排序
 head:链表头结点地址 
 isAscending:是否采用升序，升序 为TRUE，降序为FALSE 
 oneGreaterThanTwo:由用户实现的比较函数 
*/ 
void bubbleSortList(Node *head, boolean isAscending, 
	boolean (*oneGreaterThanTwo)(USER_TYPE one, USER_TYPE two));

/*
 由用户实现的比较函数，若one > two，返回TRUE
 one:待比较数据 
 two:待比较数据 
*/ 
boolean oneGreaterThanTwo(Point one, Point two);

void bubbleSortList(Node *head, boolean isAscending,
	boolean (*oneGreaterThanTwo)(USER_TYPE one, USER_TYPE two) ) {
	
	Node *ptr;
	int listLen = getLength(head);
	int i,j;
	USER_TYPE temp;
	boolean flag;
	
	for (i = 0; i < listLen-1; i++) {
		ptr = head; //需要保存头指针 
		for (j = 0; j < listLen-i-1; j++) {
			//升序或者降序 
			isAscending == TRUE ? (flag = oneGreaterThanTwo(ptr->value,
				ptr->next->value))
				: (flag = oneGreaterThanTwo(ptr->next->value, ptr->value));
			if (flag) {
				temp = ptr->value;
				ptr->value = ptr->next->value;
				ptr->next->value = temp;
			}
			ptr = ptr->next;
		}
	}
}

boolean motifyNodeByIndex(Node *head, USER_TYPE value, int index) {
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

int getLength(Node *head) {
	int cnt = 0;
	
	while (head != NULL) {
		cnt++;
		head = head->next;	
	}
	return cnt;
}

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

boolean deleteNode(Node **pHead, int pos) {	
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

boolean frontInsertNode(Node **pHead, USER_TYPE value, int pos) {
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

boolean behindInsertNode(Node *head, USER_TYPE value, int pos) {
	Node *current;
	if (pos < 0) {
		return FALSE;
	}

	while (head != NULL) {
		if (pos-- == 1) {
			current = (Node*)malloc(sizeof(Node));
			current->value = value;
			current->next = head->next;
			head->next = current;
			return TRUE;
		} 
		head = head->next;
	}
	return FALSE;
}

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

void printLinkedList(Node *head) {
	puts("结果如下：");
	while (head != NULL) {
		printf("(%d,%d) ", head->value.row, head->value.col);
		head = head->next;
	}
}

boolean initLinkedList(Node **pHead, boolean (*inputValue)(USER_TYPE*)) {
	Node *current = NULL;
	Node *prev = NULL;
	USER_TYPE value;
	
	if (*pHead != NULL) {
		return FALSE;
	}
	
	while (TRUE == inputValue(&value)) {
		current = (Node*)malloc(sizeof(Node));
		current->value.row = value.row;
		current->value.col = value.col;
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

boolean oneGreaterThanTwo(Point one, Point two) {
	if (((one.row*one.row + one.col*one.col) 
		- (two.row*two.row + two.col*two.col)) > 0) {
		return TRUE;
	}
	return FALSE;
}

boolean inputPoint(Point *point) {
	printf("输入点坐标(ctrl+Z结束):");
	return 2 == scanf("%d%d", &(point->row), &(point->col)); 
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
 	//motifyNodeByIndex(head, temp, 3);
	//appendValue(head, temp);
	frontInsertNode(&head, temp, 0);
	bubbleSortList(head, TRUE, oneGreaterThanTwo); 
	printLinkedList(head);

 	destoryLinkedList(&head);
	return 0;
}