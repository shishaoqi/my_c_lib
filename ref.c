/*
 * File: ref.c
 * -------------
 * This interface exports several simple functions for allocating
 * pointers to the atomic types.(P 286)
 */
#include "genlib.h"
#include "ref.h"

/*
 * Part 1 - Functions to create pointers from basic types
 * -------------------------------------------------------
 */

void *NewRefInt(int value)
{
	int *address=New(int*);
	*address=value;
    return (address);
}

void *NewRefShort(short value)
{
	short *address=New(short*);
	*address=value;
    return (address);
}

void *NewRefLong(long value)
{
    long *address=New(long*);
	*address=value;
    return (address); 
}

void *NewRefFloat(float value)
{
	float *address=New(float*);
	*address=value;
    return (address);
}

void *NewRefDouble(double value)
{
	double *address=New(double*);
	*address=value;
    return (address);
}

void *NewRefChar(char value)
{
	char *address=New(char*);
	*address=value;
    return (address);
}

void *NewRefBool(bool value)
{
	bool *address=New(bool*);
	*address=value;
    return (address);
}

void *NewRefUnsignedShort(unsigned short value)
{
	unsigned short *address=New(unsigned short*);
	*address=value;
    return (address);
}

void *NewRefUnsignedLong(unsigned long value)
{
    unsigned long *address=New(unsigned long*);
	*address=value;
    return (address);
}

void *NewRefUnsignedChar(unsigned char value)
{
	unsigned char *address=New(unsigned char*);
	*address=value;
    return (address);
}


/*
 * Part 2 - Functions to dereference generic pointers
 *===================================================
 */
int RefToInt(void *ref)
{
  int value = *(int*)ref;
  FreeBlock(ref);
  return value;
}

short RefToShort(void *ref)
{
  short value=*(short*)ref;
  FreeBlock(ref);
  return value;
}

long RefToLong(void *ref)
{
   long value=*(long*)ref;
   FreeBlock(ref);
   return value;
}

float RefToFloat(void *ref)
{
  float value=*(float*)ref;
  FreeBlock(ref);
  return value;
}

double RefToDouble(void *ref)
{
  double value=*(double*)ref;
  FreeBlock(ref);
  return value;
}

char RefToChar(void *ref)
{
  char value=*(char*)ref;
  FreeBlock(ref);
  return value;
}

bool RefToBool(void *ref) 
{
  bool value=*(bool*)ref;
  FreeBlock(ref);
  return value;
}

unsigned RefToUnsigned(void *ref)
{
  unsigned value=*(unsigned*)ref;
  FreeBlock(ref);
  return value;
}

unsigned short RefToUnsignedShort(void *ref)
{
  unsigned short value=*(unsigned short*)ref;
  FreeBlock(ref);
  return value;
}

unsigned long RefToUnsignedLong(void *ref)
{
  unsigned long value=*(unsigned long*)ref;
  FreeBlock(ref);
  return value;
}

unsigned char RefToUnsignedChar(void *ref)
{
  unsigned char value=*(unsigned char*)ref;
  FreeBlock(ref);
  return value; 
}
