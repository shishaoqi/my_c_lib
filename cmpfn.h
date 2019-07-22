/*
 * File: comfn.h
 * -------------
 * This interface exports several comparison functions for use 
 * with ANSI library functions like qsort and bsearch as well
 * as various functions in the exeended library.
 */
#ifndef _cmpfn_h
#define _cmpfn_h

/* 
 * Type: cmpFnT
 *--------------
 * This type defines the type space of comparison functions,
 * each of which take the addresses of their arguments and 
 * whether the first argument is less than, equalto, or 
 * greater than the second.  
 * 
 * 比如用在：void qsort(void *array, int n, int elementSize, comFnT comFn, exchFnT fn);
 */
typedef int (*cmpFnT) (const void *p1, const void *p2);
typedef void (*exchFnT) (void *p1, void *p2);

/*
 * Type: StringBox
 * ----------------
 */
struct Str{
  string s;
};

typedef struct Str *StringBox;

/*
 * Standard comparison functions
 *-------------------------------
 * The remainder of this interface exports standard comparison
 * functions for the most common built-in types.
 */

int IntCmpFn(const void *p1, const void *p2);
int ShortCmpFn(const void *p1, const void *p2);
int LongCmpFn(const void *p1, const void *p2);
int LonglongCmpFn(const void *p1, const void *p2);
int UnsignedIntCmpFn(const void *p1, const void *p2);
int UnsignedShortCmpFn(const void *p1, const void *p2);
int UnsignedLongCmpFn(const void *p1, const void *p2);
int UnsignedLonglongCmpFn(const void *p1, const void *p2);
int CharCmpFn(const void *p1, const void *p2);
int FloatCmpFn(const void *p1, const void *p2);
int DoubleCmpFn(const void *p1, const void *p2);
int StringCmpFn(const void *p1, const void *p2);
int StringCmpFn2(const void *p1, const void *p2);


/* 交换函数指针 */
void IntExchFn(void *p1, void *p2);
void ShortExchFn(void *p1, void *p2);
void LongExchFn(void *p1, void *p2);
void UnsignedExchFn(void *p1, void *p2);
void UnsignedShortExchFn(void *p1, void *p2);
void UnsignedLongExchFn(void *p1, void *p2);
void CharExchFn(void *p1, void *p2);
void FloatExchFn(void *p1, void *p2);
void DoubleExchFn(void*p1, void *p2);
void StringExchFn(void *p1, void *p2);

#endif
