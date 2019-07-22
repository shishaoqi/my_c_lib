/*
 * Fille: queue.h
 * ---------------
 * This function define an abstraction for queues. In any
 * single application that uses this interface, the values in
 * the queue are constrained to a single type, although it
 * is easy to change that type by changing the definition of
 * queueElementT in this interface.
 */
#ifndef _queue_h
#define _queue_h

#include "genlib.h"

typedef void *queueElementT;

typedef struct queueCDT *queueADT;

queueADT NewQueue(void);
void FreeQueue(queueADT queue);

void Enqueue(queueADT quue, queueElementT element);
queueElementT Dequeue(queueADT queue);

bool QueueIsEmpty(queueADT queue);
bool QueueIsFull(queueADT queue);
int QueueLength(queueADT queue);

queueElementT GetQueueElement(queueADT queue, int index);

#endif

