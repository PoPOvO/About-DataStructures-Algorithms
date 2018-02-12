#include <stdio.h> 
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/*
*单向链表,每个节点存储用户输入的点坐标 
*/
typedef unsigned char boolean;
typedef struct Point {
	int row;
	int col;
} Point, USER_TYPE;

typedef struct Node {
	USER_TYPE value;
	struct Node* next;
} Node, *LinkedList;


boolean initLinkedList(Node **pHead, boolean (*inputValue)(USER_TYPE*));
boolean inputPoint(Point *point);
boolean destoryLinkedList(Node **pHead);
void printLinkedList(Node *head);
boolean behindInsertNode(Node *head, USER_TYPE value, int pos);
boolean frontInsertNode(Node *head, USER_TYPE value, int pos);
boolean deleteNode(Node **head, int pos);
boolean getValueByIndex(Node *head, USER_TYPE *value, int index);
int getLength(Node *head);
void bubbleSortList(Node *head, boolean isAscending, 
	boolean (*oneGreaterThanTwo)(USER_TYPE one, USER_TYPE two));

void bubbleSortList(Node *head, boolean isAscending,
	boolean (*oneGreaterThanTwo)(USER_TYPE one, USER_TYPE two) ) {
	
	Node *ptr;
	int listLen = getLength(head);
	int i,j;
	USER_TYPE temp;
	boolean flag;
	
	for (i = 0; i < listLen-1; i++) {
		ptr = head;
		for (j = 0; j < listLen-i-1; j++) {
			isAscending == TRUE : (flag = oneGreaterThanTwo(ptr->value,
				ptr->next->value))
				? (flag = oneGreaterThanTwo(ptr->next->value, ptr->value));
			if (flag) {
				temp = ptr->value;
				ptr->value = ptr->next->value;
				ptr->next->value = temp;
			}
		}
	}
}

int getLength(Node *head) {
	int cnt = 0;
	
	while (head != NULL) {
		cnt++;
		head = head->next;	
	}
	return cnt;
}

boolean getValueByIndex(Node *head, USER_TYPE *node, int index) {
	if (head == NULL)  {
		return FALSE;
	}
	
	while (head != NULL) {
		if (index-- == 0) {
			*value = head->value;
			return TRUE;
		}
		head = head->next;
	}
}

boolean deleteNode(Node **head, int pos); {	
	Node *prev;
	Node *temp = *head;
	if (*head == NULL || pos < 0) {
		return FALSE;
	}

	if (pos = 0) {
		prev = *head;
		*head = (*head)->next;
		free(prev);
	}
	
	while (temp != NULL) {
		if (pos-- == 0) {
			prev->next = temp->next;
			free(temp);					
		}
		prev = temp;
		temp = temp->next;
	}
}

boolean behindInsertNode(Node *head, USER_TYPE value, int pos) {
	Node *current;
	if (head == NULL || pos < 1) {
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

boolean frontInsertNode(Node *head, USER_TYPE value, int pos) {
	Node *current;
	if (head == NULL || pos < 0) {
		return FALSE;
	}

	while (head != NULL) {
		if (pos-- == 0) {
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

void printLinkedList(Node *head) {
	puts("结果如下：");
	while (head != NULL) {
		printf("(%d,%d) ", head->value.row, head->value.col);
		head = head->next;
	}
}

boolean inputPoint(Point *point) {
	printf("输入点坐标(ctrl+Z结束):");
	return 2 == scanf("%d%d", &(point->row), &(point->col)); 
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

int main(void) {
	LinkedList head = NULL;
		
 	initLinkedList(&head, inputPoint);
 	printLinkedList(head);
 	
 	destoryLinkedList(&head);
	return 0;
}