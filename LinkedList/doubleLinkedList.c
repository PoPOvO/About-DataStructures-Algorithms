/*
 不带头节点双向循环链表
*/

#include <stdio.h> 
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

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
	struct Node* prev; 
} Node, *LinkedList;


boolean initLinkedList(Node **pHead, boolean (*inputValue)(USER_TYPE*));
boolean inputPoint(Point *point);
boolean destoryLinkedList(Node **pHead); 
void printLinkedList(Node *head);

void printLinkedList(Node *head) {
	Node *ptr = head->next;
	puts("结果如下:");

	//先打印头节点 
	printf("(%d, %d)", head->value.row, head->value.col); 
	while (ptr != head) {
		printf("(%d, %d)", ptr->value.row, ptr->value.col);
		ptr = ptr->next; 
	}
}

boolean destoryLinkedList(Node **pHead) {
	Node *temp;
	Node *ptr = (*pHead)->next;
	if (*pHead == NULL) {
		return FALSE;
	}
	
									//释放头节点后面的节点 
	while (ptr != *pHead) {
 		temp = ptr->next;
		free(ptr);
		ptr = temp;
	} 
									//最后释放头节点 
	free(*pHead);
	*pHead = NULL;
	
	return TRUE; 
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
		current->value = value;
		current->next = *pHead;				//每一个新节点的next指针都先指向头节点 

		if (*pHead == NULL) {
			*pHead = prev = current;
		} else {
			prev->next = current;			//修改上一个节点的next指针为当前节点 
			current->prev = prev;  			//更改当前节点的prev指针为上一个节点 
			prev = current;
		}	
		(*pHead)->prev = current;			//无论如何，都要将头节点的prev指针指向当前，即尾节点 
	}
	return TRUE;
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
	initLinkedList(&head, inputPoint);	
	printLinkedList(head);
	destoryLinkedList(&head);
	return 0; 
} 
