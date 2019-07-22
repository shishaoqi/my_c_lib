/* 
 * File: iterator.h
 * ----------------
 * This file implements an iterator for the symbol table
 * abstraction. In the charper on "Set" this package is 
 * superseded by a more general polymorphic iterator that
 * works for other collection types as well.
 */

#ifndef _iterator1_h
#define _iterator1_h

#include "genlib.h"
#include "symtab.h"

/* 
 * Type: iteratorADT
 * -----------------
 * This abstract type is used to iterate over the elements 
 * in symbol table.
 */
typedef struct iteratorCDT *iteratorADT;

/* Exported entries */

/*
 * Functions: NewIterator, StepIterator, FreeIterator
 * Usage: iterator = NewIterator(table);
 *        while (StepIterator(iterator, &key)){
 *            . . . body of loop involving key . . .
 *        }
 *        FreeIterator(iterator);
 * --------------------------------------------------
 * These functions make it possible to iterate over the keys
 * in a symbol table without having to call a mapping function.
 * The call to NewIterator create a new iteratorADT that
 * contains all the keys in the table, arranged in ASCII order.
 * Each call to StepIterator advances the iterator and returns
 * the next key using the reference parameter. StepIterator
 * returns TRUE until the keys are exhausted, after which it 
 * returns FALSE. The FreeIterator function releases any
 * storage associated with the iterator.
 */
iteratorADT NewIterator_1(symtabADT table);
bool StepIterator_1(iteratorADT iterator, string *pKey);
void FreeIterator_1(iteratorADT iterator);

#endif
