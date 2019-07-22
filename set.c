/*
 * File: set.c
 * -------------
 * This file implements the set abstraction fefined in set.h.
 */
#include <stdio.h>
#include <string.h>
#include "genlib.h"
#include "bst.h"
#include "iterator2.h"
#include "itertype.h"
#include "set.h"

/*
 * Type: setCDT
 * -------------
 * This type defines the concrete structure of a set.
 */

struct setCDT {
    iteratorHeaderT header;
    setClassT class;
    cmpFnT cmpFn;
    int nElements;
    bstADT bst;
    int setElementSize;//新增(setElementT内存空间大小)
};

typedef union {
    int intRep;
    void *ptrRep;
} setElementT;

/* Private function  prototypes */
static setADT NewSet(int size, setClassT class, cmpFnT cmpFn);
static void InitSetNodeFn(void *np, void *kp, void *clientData);
static void FreeNodeFn(void *np, void *clientData);
static void AddERef(setADT set, void *ep);
static void DeleteERef(setADT set, void *ep);
static bool TestERef(setADT set, void *ep);
static iteratorADT NewSetIterator(void *collection);
static void AddElementToIterator(void *np, void *clientData);
static void display(void *np, void *clientData);

/* Exported entries */
setADT NewIntSet(void)
{
    int size = sizeof(int);
    return (NewSet(size, IntSet, IntCmpFn));
}

setADT NewPtrSet(int size, cmpFnT cmpFn)
{
    return (NewSet(size, PtrSet, cmpFn));
}

static setADT NewSet(int size, setClassT class, cmpFnT cmpFn)
{
    setADT set;

    set = New(setADT);
    EnableIteration(set, NewSetIterator);
    set->class = class;
    set->cmpFn = cmpFn;
    set->nElements = 0;
    set->setElementSize = size;
    set->bst = NewBST(size, cmpFn, InitSetNodeFn);
    return (set);
}

/**
 * NewBST() callback function
 * @param np         [description]
 * @param kp         [description]
 * @param clientData [description]
 */
static void InitSetNodeFn(void *np, void *kp, void *clientData)
{
    setADT set = (setADT) clientData;
    int setElementSize = set->setElementSize;

    switch (set->class) {
    case IntSet: *((int *)np) = *((int *)kp);   break;
    //case PtrSet: *((void**)np) = *((void**)kp); break;
    case PtrSet: memcpy(np, kp, setElementSize); break;
    }
    set->nElements++;
}

/*
 * Implementation notes: NewSetIterator, AddElementToIterator
 * ----------------------------------------------------------
 * These functions make it possible to use the general iterator
 * facility on sets.  For details on the general strategy, see
 * the comments in the itertype.h interface.  The comparison
 * function passed to NewIteratorList is UnsortedFn because the
 * InOrder walk already guarantees that the elements will appear
 * in sorted order.
 */
static iteratorADT NewSetIterator(void *collection)
{
    setADT set = (setADT) collection;
    int setElementSize;
    iteratorADT iterator;

    switch (set->class) {
    case IntSet: setElementSize = sizeof(int); break;
    case PtrSet: setElementSize = set->setElementSize; break;
    }
    iterator = NewIteratorList(setElementSize, UnsortedFn);
    MapBST(AddElementToIterator, set->bst, InOrder, iterator);

    return iterator;
}

/**
 * 替换  AddElementToIterator 用于测试
 * @param np         [description]
 * @param clientData [description]
 */
static void display(void *np, void *clientData)
{
    printf("%s\n", (string)np);
}

static void AddElementToIterator(void *np, void *clientData)
{
    AddToIteratorList( (iteratorADT)clientData, np);
}

void FreeSet(setADT set)
{
    FreeBST(set->bst, FreeNodeFn);
    FreeBlock(set);
}

static void FreeNodeFn(void *np, void *clientData)
{
    FreeBlock(np);
}

/* Selection functions */
setClassT GetSetClass(setADT set)
{
    return (set->class);
}

cmpFnT GetCompareFunction(setADT set)
{
    return (set->cmpFn);
}

int NElements(setADT set)
{
    return (set->nElements);
}

bool SetIsEmpty(setADT set)
{
    return (set->nElements == 0);
}

void AddIntElement(setADT set, int element)
{
    if (set->class != IntSet) Error("Set is not an iteger set");
    AddERef(set, &element);
}

void AddPtrElement(setADT set, void *element)
{
    if (set->class != PtrSet) Error("Set is not a pointer set");
    AddERef(set, element);//遗漏 &(20160425 晚) === 不需要&(20160426 晚再证，以前应该测试过，所以之前也没加&)
}

static void AddERef(setADT set, void *ep)
{
    (void) InsertBSTNode(set->bst, ep, set);
}

void DeleteIntElement(setADT set, int element)
{
    if (set->class != IntSet) Error("Set if not an integer set");
    DeleteERef(set, &element);
}

void DeletePtrElement(setADT set, void *element)
{
    if (set->class != PtrSet) Error("Set is not a pointer set");
    DeleteERef(set, element);
}

static void DeleteERef(setADT set, void *ep)
{
    if ( DeleteBSTNode(set->bst, ep) )
        set->nElements--;
}

bool IsIntElement(setADT set, int element)
{
    if (set->class != IntSet) Error("Set if not an integer set");
    return (TestERef(set, &element));
}

bool IsPtrment(setADT set, void *element)
{
    if (set->class != PtrSet) Error("Set if not an pointer set");
    return (TestERef(set, element));
}

static bool TestERef(setADT set, void *ep)
{
    return (FindBSTNode(set->bst, ep) != NULL);
}

/*
 * Implementation notes: Set operations
 * ------------------------------------
 * The function IsSubset, Union, Intersection, and SetDifference
 * are similar in structure. Each one an iterator to walk over
 * the appropriate set, Because the functions in bst.h need only
 * the address of an element, the functions can use the union type
 * setElementT to avoid special-case code for the two set classes.
 */
bool SetEqual(setADT s1, setADT s2)
{
    return (IsSubset(s1, s2) && IsSubset(s2, s1));
}

bool IsSubset(setADT s1, setADT s2)
{
    iteratorADT iterator;
    //setElementT element;
    void *element;
    bool result;
    int elementSize;

    elementSize = s1->setElementSize > s2->setElementSize ? s1->setElementSize : s2->setElementSize;
    if (s1->class != s2->class || s1->cmpFn != s2->cmpFn) {
        Error ("IsSubset: Set types do not match");
    }
    result = TRUE;
    iterator = NewIterator(s1);
    element = GetBlock(elementSize);
    while (result && StepIterator(iterator, element)) {
        if (!TestERef(s2, element)) result = FALSE;
    }
    FreeIterator(iterator);
    FreeBlock(element);
    return (result);
}

setADT Union(setADT s1, setADT s2)
{
    iteratorADT iterator;
    //setElementT element;
    void *element;
    setADT set;
    int elementSize;

    elementSize = s1->setElementSize > s2->setElementSize ? s1->setElementSize : s2->setElementSize;
    if (s1->class != s2->class || s1->cmpFn != s2->cmpFn) {
        Error("Union: Set types do not match");
    }
    set = NewSet(s1->setElementSize, s1->class, s1->cmpFn);
    iterator = NewIterator(s1);
    element = GetBlock(elementSize);
    while (StepIterator(iterator, element)) {
        AddERef(set, element);
    }
    FreeIterator(iterator);
    iterator = NewIterator(s2);
    FreeBlock(element);
    element = GetBlock(elementSize);
    while (StepIterator(iterator, element)) {
        AddERef(set, element);
    }
    FreeIterator(iterator);
    FreeBlock(element);
    return set;
}

setADT Intersection(setADT s1, setADT s2)
{
    iteratorADT iterator;
    //setElementT element;
    void *element;
    setADT set;
    int elementSize;

    elementSize = s1->setElementSize > s2->setElementSize ? s1->setElementSize : s2->setElementSize;
    if (s1->class != s2->class || s1->cmpFn != s2->cmpFn) {
        Error("Intersection: Set types do not match");
    }

    set = NewSet(s1->setElementSize, s1->class, s1->cmpFn);
    iterator = NewIterator(s1);
    element = GetBlock(elementSize);
    while (StepIterator(iterator, element)) {
        if (TestERef(s2, element)) AddERef(set, element);
    }
    FreeIterator(iterator);
    FreeBlock(element);
    return set;
}

setADT SetDifference(setADT s1, setADT s2)
{
    iteratorADT iterator;
    //setElementT element;
    void *element;
    setADT set;
    int elementSize;

    elementSize = s1->setElementSize > s2->setElementSize ? s1->setElementSize : s2->setElementSize;
    if (s1->class != s2->class || s1->cmpFn != s2->cmpFn) {
        Error("SetDifference: Set types do not match");
    }
    set = NewSet(s1->setElementSize, s1->class, s1->cmpFn);
    iterator = NewIterator(s1);
    element = GetBlock(elementSize);
    while (StepIterator(iterator, element)) {
        if (!TestERef(s2, element)) AddERef(set, element);
    }
    FreeIterator(iterator);
    FreeBlock(element);
    return set;
}


//---------------- 书里遗漏的方法 ----------------
/*
 * Implementation note: AddArrayToSet
 * ----------------------------------
 * This function calls AddERef for each element in the array.
 * Note that the addressing depends on the set class.
 */

void AddArrayToSet(setADT set, void *array, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        switch (set->class) {
            case IntSet: AddERef(set, ((int *) array) + i); break;
            case PtrSet: AddERef(set, *(((void **) array) + i)); break;
        }
    }
}
