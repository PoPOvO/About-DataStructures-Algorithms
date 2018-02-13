#include <stdio.h> 
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/*
* ��������,ÿ���ڵ�洢�û�����ĵ����� 
*/
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
} Node, *LinkedList;

/*
 ��ʼ������ 
 pHead:����ͷ�ڵ��ַ 
 inputValue����Ҫ���û�ʵ�ֵĺ��������ڶ���һ��ֵ�� 
*/ 
boolean initLinkedList(Node **pHead, boolean (*inputValue)(USER_TYPE*));

/*
 ���û�ʵ�ֵĺ��������ڶ���һ��ֵ �� 
 *point:һ������������ 
*/ 
boolean inputPoint(Point *point);

/*
 ���������ͷ����нڵ㡣
 pHead:ָ��ͷ�ڵ��ָ��ĵ�ַ 
*/ 
boolean destoryLinkedList(Node **pHead);

/*
 ��ӡ����Ԫ�ص�����̨
 head:����ͷ����ַ 
*/
void printLinkedList(Node *head);

/*
 ׷��Ԫ��
 head:����ͷ����ַ   
 value:׷������ 
*/
boolean appendValue(Node* head, USER_TYPE value); 

/*
 ��ָ��λ�ú��һ���ڵ�
 head:����ͷ����ַ 
 value:����ڵ�������� 
 pos:����λ�� 
*/
boolean behindInsertNode(Node *head, USER_TYPE value, int pos);

/*
 ��ָ��λ��ǰ��һ���ڵ�
 head:����ͷ����ַ 
 value:����ڵ�������� 
 pos:����λ�� 
*/
boolean frontInsertNode(Node **pHead, USER_TYPE value, int pos);

/*
 ��ָ��λ��ɾ��һ���ڵ㣬����Ϊͷ�ڵ� 
 pHead:ָ��ͷ�ڵ��ָ��ĵ�ַ 
 pos:ɾ���ڵ��±� 
*/ 
boolean deleteNode(Node **pHead, int pos);

/*
 �����±�õ���Ӧ�ڵ������� 
 head:����ͷ����ַ 
 value:������ͨ��ָ�뷵��
 index:�ڵ��±� 
*/ 
boolean getValueByIndex(Node *head, USER_TYPE *value, int index);

/*
 �����±��޸Ľڵ�������
 head:����ͷ����ַ 
 value:�޸ĵ����� 
 index:�ڵ��±�  
*/
boolean motifyNodeByIndex(Node *head, USER_TYPE value, int index);

/*
 �õ�������
 head:����ͷ����ַ  
*/
int getLength(Node *head);

/*
 ʹ��ð������������������
 head:����ͷ����ַ 
 isAscending:�Ƿ������������ ΪTRUE������ΪFALSE 
 oneGreaterThanTwo:���û�ʵ�ֵıȽϺ��� 
*/ 
void bubbleSortList(Node *head, boolean isAscending, 
	boolean (*oneGreaterThanTwo)(USER_TYPE one, USER_TYPE two));

/*
 ���û�ʵ�ֵıȽϺ�������one > two������TRUE
 one:���Ƚ����� 
 two:���Ƚ����� 
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
		ptr = head; //��Ҫ����ͷָ�� 
		for (j = 0; j < listLen-i-1; j++) {
			//������߽��� 
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

	//ɾ��ͷ�ڵ� 
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
	puts("������£�");
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
	printf("���������(ctrl+Z����):");
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