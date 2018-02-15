/*
 ����ͷ�ڵ�˫��ѭ������
*/

#include <stdio.h> 
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef unsigned char boolean;

/*
 ��ʾƽ���ϵĵ� 
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
	puts("�������:");

	//�ȴ�ӡͷ�ڵ� 
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
	
	//�ͷ�ͷ�ڵ����Ľڵ� 
	while (ptr != *pHead) {
 		temp = ptr->next;
		free(ptr);
		ptr = temp;
	} 
	//����ͷ�ͷ�ڵ� 
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
		current->next = *pHead;				//ÿһ���½ڵ��nextָ�붼��ָ��ͷ�ڵ� 

		if (*pHead == NULL) {
			*pHead = prev = current;
		} else {
			prev->next = current;			//�޸���һ���ڵ��nextָ��Ϊ��ǰ�ڵ� 
			current->prev = prev;  			//���ĵ�ǰ�ڵ��prevָ��Ϊ��һ���ڵ� 
			prev = current;
		}	
		(*pHead)->prev = current;			//������Σ���Ҫ��ͷ�ڵ��prevָ��ָ��ǰ����β�ڵ� 
	}
	return TRUE;
}

boolean inputPoint(Point *point) {
	printf("���������(ctrl+Z����):");
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