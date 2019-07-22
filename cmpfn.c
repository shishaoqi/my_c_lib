/*
 * File: cmpfn.cpp
 * ---------------
 */
#include "genlib.h"
#include "strlib.h"
#include "cmpfn.h"

int IntCmpFn(const void *p1, const void *p2)
{
  int v1, v2;

  v1 = *((int*)p1);
  v2 = *((int*)p2);
  if(v1 == v2) return (0);
  return ((v1<v2) ? -1:1);
}

int ShortCmpFn(const void *p1, const void *p2)
{
  short v1, v2;

  v1 = *((short*)p1);
  v2 = *((short*)p2);
  if(v1 == v2) return (0);
  return ((v1<v2) ? -1:1);
}

int LongCmpFn(const void *p1, const void *p2)
{
  long v1, v2;

  v1 = *((long*)p1);
  v2 = *((long*)p2);
  if(v1 == v2) return (0);
  return ((v1<v2) ? -1:1);
}

int LonglongCmpFn(const void *p1, const void *p2)
{
  long long v1, v2;

  v1 = *((long long*)p1);
  v2 = *((long long*)p2);
  if(v1 == v2) return (0);
  return ((v1<v2) ? -1:1);
}


int UnsignedIntCmpFn(const void *p1, const void *p2)
{
  unsigned v1, v2;

  v1 = *((int*)p1);
  v2 = *((int*)p2);
  if(v1 == v2) return (0);
  return ((v1<v2) ? -1:1);
}

int UnsignedShortCmpFn(const void *p1, const void *p2)
{
  unsigned short v1, v2;

  v1 = *((unsigned short*)p1);
  v2 = *((unsigned short*)p2);
  if(v1 == v2) return (0);
  return ((v1<v2) ? -1:1);
}

int UnsignedLongCmpFn(const void *p1, const void *p2)
{
  unsigned long v1, v2;

  v1 = *((unsigned long*)p1);
  v2 = *((unsigned long*)p2);
  if(v1 == v2) return (0);
  return ((v1<v2) ? -1:1);
}

int UnsignedLonglongCmpFn(const void *p1, const void *p2)
{
  unsigned long long v1, v2;
  
  v1 = *((unsigned long long*)p1);
  v2 = *((unsigned long long*)p2);
  if(v1 == v2) return (0);
  return ((v1<v2) ? -1:1);
}

int CharCmpFn(const void *p1, const void *p2)
{
  char v1, v2;

  v1 = *((char*)p1);
  v2 = *((char*)p2);
  if(v1 == v2) return (0);
  return ((v1<v2) ? -1:1);
}

int FloatCmpFn(const void *p1, const void *p2)
{
  float v1, v2;

  v1 = *((float*)p1);
  v2 = *((float*)p2);
  if(v1 == v2) return (0);
  return ((v1<v2) ? -1:1);
}

int DoubleCmpFn(const void *p1, const void *p2)
{
  double v1, v2;

  v1 = *((double*)p1);
  v2 = *((double*)p2);
  if(v1 == v2) return (0);
  return ((v1<v2) ? -1:1);
}

int StringCmpFn(const void *p1, const void *p2)
{
  return StringCompare( (string)p1, (string)p2 );
}

int StringCmpFn2(const void *p1, const void *p2)
{
  StringBox s1, s2;
  s1 = (StringBox)p1;
  s2 = (StringBox)p2;
  return StringCompare((s1->s), (s2->s));
}

/* 交换函数的实现
 *
 *交换 P1与P2的值
 */
void IntExchFn(void *p1, void *p2)
{
	int temp;
	temp = *(int*)p1;
	*(int*)p1 = *(int*)p2;
	*(int*)p2 = temp;
}
void ShortExchFn(void *p1, void *p2)
{
	short temp;
	temp = *(short*)p1;
	*(short*)p1 = *(short*)p2;
	*(short*)p2 = temp;
}
void LongExchFn(void *p1, void *p2)
{
	long temp;
	temp = *(long*)p1;
	*(long*)p1 = *(long*)p2;
	*(long*)p2 = temp;
}
void UnsignedExchFn(void *p1, void *p2)
{
	unsigned temp;
	temp = *(unsigned*)p1;
	*(unsigned*)p1 = *(unsigned*)p2;
	*(unsigned*)p2 = temp;
}
void UnsignedShortExchFn(void *p1, void *p2)
{
	unsigned short temp;
	temp = *(unsigned short*)p1;
	*(unsigned short*)p1 = *(unsigned short*)p2;
	*(unsigned short*)p2 = temp;
}
void UnsignedLongExchFn(void *p1, void *p2)
{
	unsigned long temp;
	temp = *(unsigned long*)p1;
	*(unsigned long*)p1 = *(unsigned long*)p2;
	*(unsigned long*)p2 = temp;
}
void CharExchFn(void *p1, void *p2)
{
	char temp;
	temp = *(char*)p1;
	*(char*)p1 = *(char*)p2;
	*(char*)p2 = temp;
}
void FloatExchFn(void *p1, void *p2)
{
	float temp;
	temp = *(float*)p1;
	*(float*)p1 = *(float*)p2;
	*(float*)p2 = temp;
}
void DoubleExchFn(void *p1, void *p2)
{
	double temp;
	temp = *(double*)p1;
	*(double*)p1 = *(double*)p2;
	*(double*)p2 = temp;
}
void StringExchFn(void *p1, void *p2)
{
	string temp;
	temp = *(string*)p1;
	*(string*)p1 = *(string*)p2;
	*(string*)p2 = temp;
}
