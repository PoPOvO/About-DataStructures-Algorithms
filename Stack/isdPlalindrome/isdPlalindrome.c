#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef unsigned char USER_TYPE;

#include "stack.h"

int isPlalindrome(Stack *stack, char* str);
int isPlalindrome(Stack *stack, char* str) {
	int strLen = strlen(str);
 	int mid = strLen/2;
	char value;
	
	mid = strLen/2;
	while (stack->top < mid) {
		push(stack, str[stack->top]);
	}
	
	if (strLen % 2 == 1) mid++;           //�������ַ��Թ����м� 
	while (mid < strLen) {
		pop(stack, &value);
		if (value != str[mid++]) return 0;
	}
	return 1;
}

//hellolleh
//aba
int main(void) {
	Stack *stack = NULL; 
	unsigned int strLen = 0;
	char *str = NULL;
	
	printf("������Ĵ�����:");
	scanf("%d", &strLen);
	str = (char*)calloc(sizeof(char), strLen + 1);
	printf("������Ĵ�:");
	scanf("%s", str);
	
	if (strlen(str) != strLen) {
		puts("�ַ������Ȳ�ƥ�䣡");
		destroyStack(&stack);
		free(str);
		return 0;
	}
	
	initStack(&stack, strLen/2);
	printf("[%s]%s���Ĵ�\n", str, isPlalindrome(stack, str) == 1 ? "��" : "����");
	
	destroyStack(&stack);
	free(str);
	return 0;
}