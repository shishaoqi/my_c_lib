/*
 * File: qlist.c
 * -------------
 * This file implements the queue.h abstraction using a linked
 * list of cells.
 */
#include <stdio.h>
#include "genlib.h"
#include "queuelist.h"

/* 
 * Type: cellT
 * -----------
 * This type defines the cells used for the linked list that
 * stores the items in the queue.
 */
typedef struct cellT{
	queueElementT value;
	struct cellT *link;
} cellT;
 
struct queueCDT{
	cellT *head;
	cellT *tail;
};

/* Exported entries */
queueADT NewQueue(void){
	queueADT queue;

	queue=New(queueADT);
	queue->head = NULL;
	return queue;
}

void FreeQueue(queueADT queue){
	cellT *cp, *next;
	cp = queue->head;
	while(cp!=NULL){
		next = cp->link;
		FreeBlock(cp);
		cp=next;
	}
	FreeBlock(queue);
}

void Enqueue(queueADT queue, queueElementT element){
	cellT *cp;

	cp = New(cellT *);
	cp->value=element;
	cp->link=NULL;

	if(queue->head == NULL)
		queue->head = queue->tail = cp; 
	else{
		queue->tail->link = cp;
		queue->tail = queue->tail->link;
	}
}

queueElementT Dequeue(queueADT queue){
	queueElementT result;
	cellT *cp;

	cp = queue->head;
	if(cp == NULL) Error("Dequeue: queue is empty");
	result = cp->value;
	queue->head = cp->link;
	FreeBlock(cp);
	return result;
}

bool QueueIsEmpty(queueADT queue){
	return (queue->head == NULL);
}

bool QueueIsFull(queueADT queue){
	return (FALSE);
}

int QueueLength(queueADT queue)
{
	int n=0; 
	cellT *cp;

	for(cp=queue->head; cp!=NULL; cp=cp->link) n++;
	return n;
}
	 
queueElementT GetQueueElement(queueADT queue, int index)
{
	int i;
	cellT *cp;

	if(index < 0 || index>=QueueLength(queue))
		Error("Queue element is out of range");

	cp = queue->head;
	for(i=0; i<index; i++) cp=cp->link;
	return cp->value;
}
