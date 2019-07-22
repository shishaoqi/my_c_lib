/* 
 * File: iterator.c
 * -----------------
 * This file implements an iterator for the symbol table
 * abstraction. In Chapter 14, this package is superseded
 * by a more general polymorphic iterator that also works for 
 * oher types that represent collections.
 */

#include <stdio.h>
#include "genlib.h"
#include "strlib.h"
#include "symtab.h"
#include "iterator1.h"

typedef struct cellT{
	string key;
	struct cellT *link;
} cellT;

struct iteratorCDT{
	cellT *start;
};

static void InsertKey(string key, void *value, void *clientData);

iteratorADT NewIterator_1(symtabADT table)
{
	iteratorADT iterator;

	iterator = New(iteratorADT);
	iterator->start = NULL;
	MapSymbolTable(InsertKey, table, iterator);
	return (iterator);
}

bool StepIterator_1(iteratorADT iterator, string *pKey)
{
	cellT *cp;

	cp = iterator->start;
	if(cp == NULL) return (FALSE);
	*pKey = cp->key;
	iterator->start = cp->link;
	FreeBlock(cp);
	return (TRUE);
}

void FreeIterator_1(iteratorADT iterator)
{
	cellT *cp;
	 
	while((cp = iterator->start) != NULL){
		iterator->start = cp->link;
		FreeBlock(cp);
	}
	FreeBlock(iterator);
}

/* 
 * Function: InsertKey
 * Usage; MapSymbolTable(InsertKey, table, iterator);
 * ---------------------------------------------------
 * This function is a callback function callled by MapSymbolTable
 * on every entry in a symbol table. Its effect is to insert 
 * the current key into the linked list so thatthe orderof the
 * keys is maintained in sorted order, The code is a simple
 * find-and-insert ollp that ends with prev and next pointing to 
 * the cells on each side ofthe insertion point. As a special
 * case, a NULL value for prev indicates insertion at the beginning.
 */
static void InsertKey(string key, void *value, void *clientData)
{
	iteratorADT iterator;
	cellT *prev, *next, *cp;

	iterator = (iteratorADT) clientData;
	prev = NULL;
	next = iterator->start;

    while( next != NULL && StringCompare(key, next->key)>0 ){
		prev = next;
		next = next->link;
	}
	cp = New(cellT *);
	cp->key = key;
	cp->link = next;

	if(prev == NULL){
		iterator->start = cp;
	}else{
		prev->link = cp;
	}
}
