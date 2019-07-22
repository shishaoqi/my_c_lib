/*
 * File: stack.h
 * ����(������Ƴ���˼�롪��C���������� P263
 *
*/

#ifndef _stack_h
#define _stack_h

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


