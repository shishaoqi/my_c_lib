/*
 * File: ref.h
 * -------------
 * This interface exports several simple functions for allocating
 * pointers to the atomic types.(P 286)
 */
#ifndef _ref_h
#define _ref_h

/*
 * Part 1 - Functions to create pointers from basic types
 * -------------------------------------------------------
 * These functions take a value of one of the built-in types and 
 * copy it into dynamically allocated memory. The result is a 
 * pointer to the newly allocated value. For example, calling 
 * NewRefInt(i) returns a pointer to a copy of the integer i.
 */

void *NewRefInt(int value);
void *NewRefShort(short value);
void *NewRefLong(long value);
void *NewRefFloat(float value);
void *NewRefDouble(double value);
void *NewRefChar(char value);
void *NewRefBool(bool valve);
void *NewRefUnsignedShort(unsigned short value);
void *NewRefUnsignedLong(unsigned long value);
void *NewRefUnsignedShort(unsigned short value);
void *NewRefUnsignedChar(unsigned char value);

/*
 * Part 2 - Functions to dereference generic pointers
 * ---------------------------------------------------
 * These functions take a generic, which must be of the type void* and return 
 * the value to which it points , which must be of the type indicated 
 * as a pointer to an int and returns the integer at that address.
 */

int RefToInt(void *ref);
short RefToShort(void *ref);
long RefToLong(void *ref);
float RefToFloat(void *ref);
double RefToDouble(void *ref);
char RefToChar(void *ref);
bool RefToBool(void *ref); 
unsigned RefToUnsigned(void *ref);
unsigned short RefToUnsignedShort(void *ref);
unsigned long RefToUnsignedLong(void *ref);
unsigned char RefToUnsignedChar(void *ref);

#endif

