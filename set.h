/*
 * File: set.h
 * ------------
 * This interface exports the type setADT, which can be used
 * to represent sets of objects. The bojects themselves can 
 * be either of the following two types:
 * int
 * void *
 *
 * In addition to the set operations shown int this interface;
 * the set type allows iteration, as describdd in the iterator.h
 * interface. The standard iterator idiom looks like this:
 *
 *    iterator = NewIterator(s);
 *    while (StepIterator(iterator, &x)){
 *      . . . body of loop involving x . . .
 *    }
 *    FreeIterator (iterator);
 */
#ifndef _set_h
#define _set_h

#include "genlib.h"
#include "cmpfn.h"
 
#define MAXSTRING 50

/*
 * Type: setClassT
 * ---------------
 * This enumeration type defines the two possible set class.
 */
typedef enum { IntSet, PtrSet } setClassT;

/*
 * Type: setADT
 * ------------
 * This type defines the abstract set type. Depending on how
 * you initialize it, a set may be of either class.
 */
typedef struct setCDT *setADT;

/* Exported entries */

/* 
 * Functions: NewIntSet, NewPtrSet
 * Usage: set = NewIntSet();
 *        set = NewPtrSet(cmpFn);
 * -------------------------------
 * These functions aer used to create empty setADT values of the 
 * specified class. The NewIntSet function creates sets capable
 * of holding integers. The NewPtrSet function creates a more 
 * general set type capable of holding client-specified types
 */
setADT NewIntSet(void);
setADT NewPrtSet(int size, cmpFnT cmpFn);

/*
 * Function: FreeSet
 * Usage: FreeSet(set)
 * -------------------------------
 * This function frees the storage assiciated with set, whicth
 * mya be of either class.
 */
void FreeSet(setADT set);

/*
 * Functions: GetSetClass, GetCompareFunction
 * Usage: class = GetSetClass(set);
 *        fn = GetCompareFunction(set);
 * ------------------------------------
 * These functions return the set class and the comparison
 * function for an existing set.
 */
setClassT GetSetClass(setADT set);
cmpFnT GetCompareFunction(setADT set);

/*
 * Function: NElementss
 * Usage: n = NElements(set);
 * -----------------------------
 * This function return the number of elements in the set.
 */
int NElements(setADT set);

/*
 * Function: SetIsEmpty
 * Usage: if (SetIsEmpyt(set))...
 * -------------------------------------------
 * This function return TRUE if the set has no elements.
 */
bool SetIsEmpty(setADT set);

/*
 * Functions: AddIntElement, AddPtrElement
 * Usage:  AddIntElement (set, element);
 *         AddPtrElement (set, element);
 * -------------------------------------------
 * These functions each add a new element to an existing set
 * and differ only in the type of that element.
 */
void AddIntElement(setADT set, int element);
void AddPtrElement(setADT set, void *element);

/*
 * Functions: DeleteIntElement, DeletePtrElement
 * Usage:  DeleteIntElement(set, element);
 *         DeletePtrElement(set, element);
 * -------------------------------------------
 * These functions delete the element from the set, if it exists,
 */
void DeleteIntElement(setADT set, int element);
void DeletePtrElement(setADT set, void *element);

/*
 * Functions: IsIntElement, IsPtrElement
 * Usage: if (IsIntElement(set, element)) ...
 *        if (IsPtrElement(set, element)) ...
 * -------------------------------------------
 * These functions return TRUE if the element is in the set.
 */
bool IsIntElement(setADT set, int element);
bool IsPtrElement(setADT set, void *element);

/*
 * Functions: SetEqual, IsSubset
 * Usage: if (SetEqual(s1, s2)) 
 *        if (IsSubset(s1, s2))
 * -------------------------------------------
 * These predicate functions implement the equality and subset
 * relations on sets, resectively. SetEqual(s1, s2) returns
 * TRUE if s1 and s2 have the same of elements. IsSubset(s1, s2)
 * returns TRUE if all elements of s1 are alse elements of s2.
 */
bool SetEqual(setADT s1, setADT s2);
bool IsSubset(setADT s1, setADT s2);

/*
 * Functions: Union, Intersection, SetDifference
 * Usage: set = Union(s1, s2);
          set = Intersetion(s1, s2);
		  set = SetDifference(s1, s2);
 * ------------------------------------
 * These functions each return a new set, as follows:
 * Union(s1, s2)               All elements in Either s1 or s2.
 * Intersetion(s1, s2)         All elements in both s1 and s2.
 * set = SetDifference(s1, s2) All elements in s1 but not in s2.
 */
setADT Union(setADT s1, setADT s2);
setADT Intersection(setADT s1, setADT s2);
setADT SetDifference(setADT s1, setADT s2);

//---------------- 书里课后练习添加的方法 ----------------
/*
 * Function: AddArrayToSet
 * Usage: AddArrayToSet(set, array, n);
 * ------------------------------------
 * This function adds the elements in the specified array to the
 * set.  The parameter n gives the effective size of the array.
 * The client is responsible for ensuring that the type of the
 * array matches the element type of the set.
 */

void AddArrayToSet(setADT set, void *array, int n);
#endif
