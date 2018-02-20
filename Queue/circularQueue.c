/*
 循环队列 
*/
#include <stdio.h>
#include <malloc.h>

#define TRUE 	1
#define FALSE 	0

typedef unsigned char boolean; 

/*
 表示平面上的点 
*/ 
typedef struct Point {
	int row;
	int col;
} Point, USER_TYPE;

typedef struct {
	int in;
	int out;
	int capacity;
	USER_TYPE *arrays;
	boolean isLastIn; 
} Queue;

boolean initQueue(Queue **pQueue, int capacity);
boolean destroyQueue(Queue **pQueue);
boolean resetQueue(Queue *queue);
boolean isFull(Queue queue);
boolean isEmpty(Queue queue);
int getElementCount(Queue queue);
boolean elementIn(Queue *queue, USER_TYPE value);
boolean elementOut(Queue *queue, USER_TYPE *value);
boolean readQueueTail(Queue queue, USER_TYPE *value);

boolean readQueueTail(Queue queue, USER_TYPE *value) {
	if (isEmpty(queue)) {
		return FALSE;
	}
	
	*value = queue.arrays[queue.out];
	return TRUE;
} 

boolean elementOut(Queue *queue, USER_TYPE *value) {
	if (queue == NULL || isEmpty(*queue)) {
		return FALSE;
	}
	
	*value = queue->arrays[queue->out];
	queue->out = (queue->out + 1) % queue->capacity;
	queue->isLastIn = FALSE;
	return TRUE;
}

boolean elementIn(Queue *queue, USER_TYPE value) {
	if (queue == NULL || isFull(*queue)) {
		return FALSE;
	}
	
	if (getElementCount(*queue) == queue->capacity-1) {		//最后一个位置被填充 
		queue->isLastIn = TRUE; 
	}
	queue->arrays[queue->in] = value;
	queue->in = (queue->in+1) % queue->capacity;
	return TRUE;
}


int getElementCount(Queue queue) {
 	return queue.isLastIn == TRUE 
	 ? queue.capacity 
	 : (queue.in - queue.out + queue.capacity) % queue.capacity;
}

boolean isEmpty(Queue queue) {
	return queue.in == queue.out && queue.isLastIn == FALSE;
}

boolean isFull(Queue queue) {
	return queue.isLastIn == TRUE;			//最后一个空位被占用则满 
}

boolean resetQueue(Queue *queue) {
	if (queue == NULL) {
		return FALSE;
	}
	queue->in = queue->out = 0;
	queue->isLastIn = FALSE; 
	return TRUE;
}

boolean destroyQueue(Queue **pQueue) {
	if (*pQueue == NULL) {
		return FALSE;
	}
	free((*pQueue)->arrays);
	free(*pQueue);
	*pQueue = NULL;
	return TRUE;
}

boolean initQueue(Queue **pQueue, int capacity) {
	if (*pQueue != NULL || capacity	<= 0) {
		return FALSE;
	}
	
	*pQueue = (Queue*)malloc(sizeof(Queue));
	(*pQueue)->arrays = (USER_TYPE*)malloc(sizeof(USER_TYPE)*capacity);
	(*pQueue)->in = (*pQueue)->out = 0;
	(*pQueue)->capacity = capacity;
	(*pQueue)->isLastIn = FALSE;
	return TRUE;
}

int main(void) {
	Queue *queue = NULL;
	Point one = {
		0,0
	};
	int i = 0;
	int capacity = 4;
	
	initQueue(&queue, capacity); 
	
	for (i; i < capacity; i++) {	
		elementIn(queue, one);
		one.row++;
		one.col++;
	}	
	printf("**current queue:[length=%d,isFull=%s,isEmpty=%s]\n",
		getElementCount(*queue), isFull(*queue) == TRUE ? "TRUE"
		: "FALSE", isEmpty(*queue) == TRUE ? "TRUE" : "FALSE");
		
	for (i; i > 0; i--) {
		elementOut(queue, &one);
		printf("%d/%d:(%d, %d)\n", capacity-i, capacity, one.row, one.col);
	}
	printf("**current queue:[length=%d,isFull=%s,isEmpty=%s]\n",
		getElementCount(*queue), isFull(*queue) == TRUE ? "TRUE"
		: "FALSE", isEmpty(*queue) == TRUE ? "TRUE" : "FALSE");
	
	elementIn(queue, one);
	readQueueTail(*queue, &one);
	printf("queue tail:(%d, %d)\n", one.row, one.col);
	printf("**current queue:[length=%d,isFull=%s,isEmpty=%s]\n",
		getElementCount(*queue), isFull(*queue) == TRUE ? "TRUE"
		: "FALSE", isEmpty(*queue) == TRUE ? "TRUE" : "FALSE");
		
	destroyQueue(&queue);	
	return 0;
}