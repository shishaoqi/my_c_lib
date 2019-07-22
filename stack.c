/*
 * File: stack.c
 *
 */
#include <stdio.h>
#include "genlib.h"
#include "stack.h"

#define InitialStackSize 100

struct stackCDT{
	stackElementT* elements;
	int count;
	int size;
};

stackADT NewStack(void)
{
	stackADT stack;

	stack = New(stackADT);
	stack->elements = NewArray(InitialStackSize, stackElementT);
	stack->count = 0;
	stack ->size = InitialStackSize;
	return stack;
}

void FreeStack(stackADT stack)
{
	FreeBlock(stack->elements);
	FreeBlock(stack);
}

static void ExpandStack(stackADT stack)
{
	stackElementT *array;
	int i, newSize;

	newSize = stack->size*2;
	array = NewArray(newSize, stackElementT);
	for(i=0; i<stack->size; i++)
		array[i] = stack->elements[i];

	FreeBlock (stack->elements);
	stack->elements = array;
	stack->size = newSize;
}

void Push(stackADT stack, stackElementT element)
{
	if(stack->count == stack->size) ExpandStack(stack);
	stack->elements[stack->count++] = element;
}

bool StackIsEmpty(stackADT stack)
{
	return (stack->count == 0);
}

stackElementT Pop(stackADT stack)
{
	if(StackIsEmpty(stack)) Error("Pop of an empty stack");
	return (stack->elements[--stack->count]);
}

bool StackIsFull(stackADT stack)
{
	return (FALSE);
}
 
int  StackDepth(stackADT stack)
{
	return (stack->count);
}

stackElementT GetStackElement(stackADT stack, int index)
{
	if(index<0 || index >=stack->count)
		Error("Non-existent stack element");
    
	return (stack->elements[stack->count - index - 1]);
}

