/* 
 * File: itertype.h
 * -----------------
 * This file provides an interface that package designers can
 * use to export new collection types that support iteration.
 * Clients of those collection types who merely want to use
 * iterators will not need to import this interface.
 */
#ifndef _itertype_h
#define _itertype_h

#include "genlib.h"
#include "iterator2.h"
#include "cmpfn.h"

/*
 * Genreral overview
 * -------------------
 * In order to create a collection type that supports iteration
 * the implementor of the type must first alllocate space at the
 * beginning of a function pointer which allows NewIterator to make
 * a new iterator for that collection type. The implementor
 * must initialize this header in the constructor function by
 * calling EnableIteration. Ther specifiec NewIterator functions
 * for each type must perform the following operations:
 *
 * 1. Call newIteratorList to create an empty iterator.
 * 2. Call AddtrIteratorList for each element.
 * 3. Return the completed iterator.
 */

/*
 * Type: newIteratorFnT
 * -------------------------
 * This type represents the class of functions that create new
 * iterators.
 */
typedef iteratorADT (*newIteratorFnT) (void *collection);

/*
 * Constant function: UnsortedFn
 * -------------------------------
 * This constant creates a NULL function pointer that can be
 * used in place of the comparison function to indicate that the
 * values in the iterator should not be sorted. The constant 0
 * is used in place of NULL because some compilers do not allow
 * casting NULL to a function pointer.
 */
#define UnsortedFn ((cmpFnT) 0)

typedef struct{
	unsigned long password;
	newIteratorFnT newFn;
}iteratorHeaderT;
//聚集类型的底层数据结构 包含一个指向创建新迭代器的回调函数指针:

void EnableIteration(void *collection, newIteratorFnT newFn);
iteratorADT NewIteratorList(int size, cmpFnT cmpFn);
void AddToIteratorList(iteratorADT iterator, void *ep);
#endif
