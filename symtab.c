/*
 * File: symtab.c
 * --------------
 * This file implements the symbol table abstraction.
 */
#include<stdio.h>
#include"genlib.h"
#include"strlib.h"
#include"symtab.h"
#include"itertype.h"
#include"cmpfn.h"
/*
 * Constants
 * ----------
 * NBuckets  -- Number of buckets in the hash table
 */
#define NBuckets 101

/*
 * Type: cellT
 * ------------
 * This type defines a linked list cell for the symbol table.
 */
typedef struct cellT{
	string key;
	void *value;
	struct cellT *link;
}cellT;

/*
 * Type: symtabCDT
 * ------------------
 * This type defines the underlying concrete reresentation for a
 * symtabADT. These details are not relevant to and therefore
 * not exported to the client. In this implementation, the
 * underlying structure is a hash table organized as an array of
 * "buckets" in which each bucket is a linked list of elements
 * that share the same hash code.
 */
struct symtabCDT{
  iteratorHeaderT header;
  cellT *buckets[NBuckets];
};

static iteratorADT NewSymtabIterator(void *collection);
static void FreeBucketChain(cellT *cp);
static cellT *FindCell(cellT *cp, string s);
static int Hash(string s, int nBuckets);
static void AddElementToIterator(string key, void *value, void *clientData);

/* Public entries */

symtabADT NewSymbolTable(void)
{
	symtabADT table;
	int i;

	table = New(symtabADT);
        EnableIteration (table, NewSymtabIterator);
	for(i=0; i<NBuckets; i++)
		table->buckets[i] = NULL;

	return table;
}

static iteratorADT NewSymtabIterator(void *collection)
{
  symtabADT table = collection;
  iteratorADT iterator;

  iterator = NewIteratorList( sizeof(char[20]), StringCmpFn);
  MapSymbolTable(AddElementToIterator, table, iterator);
  return iterator;
}

static void AddElementToIterator(string key, void *value, void *clientData)
{
  AddToIteratorList((iteratorADT) clientData, (void *)key);
}

void FreeSymbolTable(symtabADT table)
{
	int i; 
	for(i=0; i<NBuckets; i++)
		FreeBucketChain(table->buckets[i]);
	FreeBlock(table);
}

void Enter(symtabADT table, string key, void *value)
{
	int bucket;
	cellT *cp;

	bucket = Hash(key, NBuckets);
	cp = FindCell(table->buckets[bucket], key);
	if(cp == NULL)
	{
		cp = New(cellT*);
		cp->key = CopyString(key);
		cp->link = table->buckets[bucket];
		table->buckets[bucket] = cp;
	}
	cp->value = value;
}

void *Lookup(symtabADT table, string key)
{
	int bucket;
	cellT *cp;

	bucket = Hash(key, NBuckets);
	cp = FindCell(table->buckets[bucket], key);
	if(cp == NULL)  return(UNDEFINED);
	return (cp->value);
}


void MapSymbolTable(symtabFnT fn, symtabADT table, void *clientData)
{
	int i;
	cellT *cp;

	for(i=0; i<NBuckets; i++)
		for(cp = table->buckets[i]; cp != NULL; cp = cp->link)
			fn(cp->key, cp->value, clientData);
}



/* Private functions */

/*
 * Function: FreeBucketChain
 * Usage: FreeBucketChain (cp);
 * ----------------------------
 * This function takes a chain pointer and frees all the cells
 * in that chain. Because the package makes copies of the keys,
 * this function must free the string storage as well.
 */
static void FreeBucketChain(cellT *cp)
{
	cellT *next;

	while(cp!=NULL)
	{
		next = cp->link;
		FreeBlock(cp->key);
		FreeBlock(cp);
		cp = next;
	}
}

/*
 * Function: FindCell
 * Usage: cp = FindCell (cp, key);
 * --------------------------------
 * This function finds a cell in the chain beginning at cp that
 * matches key. If a match is found, a pointer to that cell is
 * returned. If no match is found, the function returns NULL.
 */
static cellT *FindCell(cellT *cp, string key)
{
	while (cp!=NULL &&  !StringEqual (cp->key, key))
		cp = cp->link;
	return cp;
}

/*
 * Function: Hash
 * Usage: bucket = Hash (key, nBuckets);
 *--------------------------------------
 * This function takes the key and uses it to derive a hash code
 * which is an integer in the range [0, NBucket - 1]. The hash
 * code is computed using a method called linear congruence. The
 * choise of the value for Multiplier can have a significant effect
 * on the performance of the algorithm, but not on its correctness.
 */

#define Multiplier -1664117991L

static int Hash(string s, int nBuckets)
{
	int i;
	unsigned long hashcode;

	hashcode = 0;
	for(i=0; s[i] !='\0'; i++)
		hashcode = hashcode * Multiplier + s[i];
	return (hashcode % nBuckets);
}

