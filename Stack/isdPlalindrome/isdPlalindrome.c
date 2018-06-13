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
	
	if (strLen % 2 == 1) mid++;           //奇数个字符略过最中间 
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
	
	printf("输入回文串长度:");
	scanf("%d", &strLen);
	str = (char*)calloc(sizeof(char), strLen + 1);
	printf("输入回文串:");
	scanf("%s", str);
	
	if (strlen(str) != strLen) {
		puts("字符串长度不匹配！");
		destroyStack(&stack);
		free(str);
		return 0;
	}
	
	initStack(&stack, strLen/2);
	printf("[%s]%s回文串\n", str, isPlalindrome(stack, str) == 1 ? "是" : "不是");
	
	destroyStack(&stack);
	free(str);
	return 0;
}