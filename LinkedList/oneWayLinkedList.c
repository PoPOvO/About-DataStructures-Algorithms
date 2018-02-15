/*
 ����ͷ�ڵ㵥������,ÿ���ڵ�洢�û�����ĵ����� 
*/
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

typedef struct Node {
	USER_TYPE value;
	struct Node* next;
} Node, *LinkedList;

boolean initLinkedList(Node **pHead, boolean (*inputValue)(USER_TYPE*)); //��ʼ������ 
boolean destoryLinkedList(Node **pHead);                                 //�������� 
void printLinkedList(Node *head);										 //��ӡ���� 
boolean appendValue(Node* head, USER_TYPE value);                        //׷�� 
boolean insertNode(Node **pHead, USER_TYPE value, int pos);         	 //���� 
boolean deleteNodeByIndex(Node **pHead, int pos);                        //ɾ���ڵ� 
boolean getValueByIndex(Node *head, USER_TYPE *value, int index);        //�鿴�ڵ����� 
boolean modifyNodeByIndex(Node *head, USER_TYPE value, int index);       //�޸Ľڵ����� 
int getLength(Node *head);                                               //��ȡ������ 
int indexOf(Node *head, USER_TYPE value, 								 //�õ���һ��ƥ��Ԫ�ص��±� 
	boolean (*equals)(USER_TYPE one, USER_TYPE two)); 
void bubbleSortList(Node *head, boolean isAscending,                     //���� 
	boolean (*oneGreaterThanTwo)(USER_TYPE one, USER_TYPE two));     
boolean iterator(Node *head, void (*operatorValue)(USER_TYPE value));    //��������е��� 

boolean oneGreaterThanTwo(Point one, Point two);                         //�û�ʵ�ֵıȽϴ�С���� 
boolean equals(Point one, Point two);									 //�û�����ıȽ���Ⱥ���
boolean inputPoint(Point *point);										 //�û�ʵ�ֵ����뺯�� 

/*
 ���û�ʵ�ֵ����뺯�������ڶ���һ��ֵ �� 
 *point:һ������������ 
*/ 
boolean inputPoint(Point *point) {
	printf("���������(ctrl+Z����):");
	return 2 == scanf("%d%d", &(point->row), &(point->col)); 
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
 ��������б���
 head:����ͷ�ڵ��ַ 
 operatorValue�����û�ʵ�֣�������Ԫ�ؽ��в��� 
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
 ʹ��ð������������������
 head:����ͷ�ڵ��ַ 
 isAscending:�Ƿ������������ ΪTRUE������ΪFALSE 
 oneGreaterThanTwo:���û�ʵ�ֵıȽϺ��� 
*/ 
void bubbleSortList(Node *head, boolean isAscending,
	boolean (*oneGreaterThanTwo)(USER_TYPE one, USER_TYPE two) ) {
	
	Node *ptr;
	int listLen = getLength(head);
	int i,j;
	USER_TYPE temp;
	boolean flag;
	
	for (i = 0; i < listLen-1; i++) {
		ptr = head; 			//��Ҫ����ͷָ�� 
		for (j = 0; j < listLen-i-1; j++) {
			//������߽��� 
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
 �õ���һ��������Ԫ����ȵ�Ԫ���±� 
 head:����ͷ����ַ  
 value:Ŀ��Ԫ��
 equals:�û�����ıȽϺ��� 
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
 �õ�������
 head:����ͷ����ַ  
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
 �����±��޸Ľڵ�������
 head:����ͷ����ַ 
 value:�޸ĵ����� 
 index:�ڵ��±�  
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
 �����±�õ���Ӧ�ڵ������� 
 head:����ͷ����ַ 
 value:������ͨ��ָ�뷵��
 index:�ڵ��±� 
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
 ��ָ��λ��ɾ��һ���ڵ㣬����Ϊͷ�ڵ� 
 pHead:ָ��ͷ�ڵ��ָ��ĵ�ַ 
 pos:ɾ���ڵ��±� 
*/ 
boolean deleteNodeByIndex(Node **pHead, int pos) {	
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

/*
 ��ָ��λ�ò���һ���ڵ�
 head:����ͷ����ַ 
 value:����ڵ�������� 
 pos:����λ�� 
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
 ׷��Ԫ��
 head:����ͷ����ַ   
 value:׷������ 
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
 ��ӡ����Ԫ�ص�����̨
 head:����ͷ����ַ 
*/
void printLinkedList(Node *head) {
	puts("������£�");
	while (head != NULL) {
		printf("(%d,%d) ", head->value.row, head->value.col);
		head = head->next;
	}
}

/*
 ���������ͷ����нڵ㡣
 pHead:ָ��ͷ�ڵ��ָ��ĵ�ַ 
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
 ��ʼ������ 
 pHead:����ͷ�ڵ��ַ 
 inputValue����Ҫ���û�ʵ�ֵĺ��������ڶ���һ��ֵ�� 
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