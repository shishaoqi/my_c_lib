/* 
 * File: iterator.h
 * ----------------
 * This file implements an iterator for the symbol table
 * abstraction. In the charper on "Set" this package is 
 * superseded by a more general polymorphic iterator that
 * works for other collection types as well.
 */

#ifndef _iterator2_h
#define _iterator2_h

#include "genlib.h"

/* 
 * Type: iteratorADT
 * -----------------
 * This abstract type is used to iterate over the elements 
 * in s symbol table.
 */
typedef struct iteratorCDT *iteratorADT;
typedef void* iteratorElementT;

iteratorADT NewIterator(void *collection);
bool StepIterator(iteratorADT iterator, void *ep);
//void* StepIterator(iteratorADT iterator);
void FreeIterator(iteratorADT iterator);

#endif

