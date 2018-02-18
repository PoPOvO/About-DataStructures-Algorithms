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

typedef struct Stack {
	int capacity;
	int top;
	USER_TYPE *arrays; 
} Stack;

boolean initStack(Stack **pStack, int capacity);					//初始化 
boolean destroyStack(Stack **pStack); 								//销毁栈 
boolean resetStack(Stack *stack);									//重置栈 
boolean isEmpty(Stack stack);										//判空 
boolean isFull(Stack stack);										//判满 
int push(Stack *stack, USER_TYPE value);							//入栈 
boolean pop(Stack *stack, USER_TYPE *value);						//出栈 
boolean readStackTop(Stack stack, USER_TYPE *value);				//读栈顶元素 

boolean readStackTop(Stack stack, USER_TYPE *value) {
	if (TRUE == isEmpty(stack)) {
		return FALSE;
	}
	*value = stack.arrays[--stack.top];
	return TRUE;
}

boolean pop(Stack *stack, USER_TYPE *value) {
	if (stack == NULL || TRUE ==isEmpty(*stack)) {
		return FALSE;
	}
	*value = stack->arrays[--stack->top];
	return TRUE;
}

int push(Stack *stack, USER_TYPE value) {
	if (stack == NULL || TRUE == isFull(*stack)) {
		return NOT_FOUND;
	}
	stack->arrays[stack->top++] = value;
	return stack->top;
}
	
boolean isFull(Stack stack) {
	return stack.top >= stack.capacity;	
}

boolean isEmpty(Stack stack) {
	return stack.top == 0;	
}
	
boolean resetStack(Stack *stack) {
	if (stack == NULL) {
		return FALSE;
	}
	stack->top = 0;
	return TRUE;
}

boolean destroyStack(Stack **pStack) {
	if (*pStack == NULL) {
		return FALSE;
	}
	
	free((*pStack)->arrays);
	free(*pStack);
	*pStack = NULL;
	return TRUE;
}

boolean initStack(Stack **pStack, int capacity) {
	if (*pStack != NULL) {
		return FALSE;
	}
	
	*pStack = (Stack*)malloc(sizeof(Stack));
	(*pStack)->capacity = capacity;
	(*pStack)->top = 0;
	(*pStack)->arrays = (USER_TYPE*)malloc(sizeof(USER_TYPE)*capacity);
	return TRUE;
}

int main(void) {
	Stack *stack = NULL;
	Point temp;
	Point one = {
		1, 1
	};
	
	Point two = {
		3, 3
	};
	
	Point three = {
		9, 9
	};

	initStack(&stack, 10);
	push(stack, one);
	if (push(stack, &temp) == FALSE) {
		puts("读取失败!");
	} else {
		printf("(%d, %d)", temp.row, temp.col);
	}
	
	printf("\nStack Deep:%d\n", push(stack, two));
	
	destroyStack(&stack);
	return 0;
}