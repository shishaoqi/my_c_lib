/*
 * File: liststack.h
 * ����(������Ƴ���˼�롪��C���������� P341
 * �����ǣ� p321
 *
*/

#ifndef _stacklist_h
#define _stacklist_h

#include "genlib.h"

typedef void* stackElementT;
typedef struct stackCDT *stackADT;

stackADT NewStack(void);
void FreeStack(stackADT stack);
void Push(stackADT stack, stackElementT element);
stackElementT Pop(stackADT stack);

bool StackIsEmpty(stackADT stack);
bool StackIsFull(stackADT stack);
int  StackDepth(stackADT stack);
stackElementT GetStackElement(stackADT stack, int index);

#endif

