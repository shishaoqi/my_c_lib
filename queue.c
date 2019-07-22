/* 就像在编程中碰到的情况一样，在开始编写代码之前，使用图形来准确理解队列的操作是很有好处的。
 * 使用环绕缓冲区的队列实现
 * File: qarray.c
 * ----------------
 * This file implements the queue.h abstractionusing an array.
 */

#include <stdio.h>
#include "genlib.h"
#include "queue.h"

/*
 * Constrants:
 * -----------
 *MaxQueueSize   --Maximum number of elements in the queue
 *QueueArraySize   --Size of the internal array
 */
#define MaxQueueSize 100
#define QueueArraySize (MaxQueueSize+1)

struct queueCDT{
	queueElementT elements[QueueArraySize];
	int head;
	int tail;
};

/* Exported entries */
queueADT NewQueue(void){
	queueADT queue;

	queue = New(queueADT);
	queue->head = queue->tail = 0;
	return queue;
}

void FreeQueue(queueADT queue){
	FreeBlock (queue);
}

void Enqueue(queueADT queue, queueElementT element)
{
	if (QueueIsFull(queue)) Error("Enqueue: queue is full");
	queue->elements[queue->tail]=element;
	queue->tail = (queue->tail+1)%QueueArraySize;
}

queueElementT Dequeue(queueADT queue){
	queueElementT result;
	
	if(QueueIsEmpty(queue)) Error("Dequeue: queue is empty");
	result=queue->elements[queue->head];
	queue->head = (queue->head+1)%QueueArraySize;
	return result;
}

bool QueueIsEmpty (queueADT queue)
{
	return (queue->head == queue->tail);
}

bool QueueIsFull(queueADT queue){
	return ((queue->tail+1)%QueueArraySize == queue->head);
}

/* 
 * Implementation notes: Queuelength
 * -----------------------------------
 * This function determines the number of elements by computing
 * (tail - head)% size. The size of the queue is added in at 
 * the begingning to ensure tahat thr left operand to % is always 
 * positive.
 */

int QueueLength (queueADT queue){
	return ((QueueArraySize+queue->tail-queue->head)%QueueArraySize);
}

queueElementT GetQueueElement(queueADT queue, int index){
	if (index<0 || index>=QueueLength(queue)){
		Error("Queue element is out of range");
	}
	return (queue->elements[(queue->head + index)%QueueArraySize]);
}
