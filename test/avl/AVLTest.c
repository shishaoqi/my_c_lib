/*
* @Author: shishao
* @Date:   2019-07-16 13:36:23
* @Last Modified by:   shishao
* @Last Modified time: 2019-07-23 01:08:16
*/

#include "genlib.h"
#include "cmpfn.h"
#include "avl.h"

void IntNodeInit(void *np, void *kp, void *clientData);
void display(void *np, void *clientData);
void write(void *np, void *clientData);

main()
{
  FILE *fp;
  int i=0, temp, second;
  int n = 0;
  int *delptr;

  //int num[30] = {30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  int num[100000];

  avlADT avl;

  avl = NewAVL(sizeof(int), IntCmpFn, IntNodeInit);

  Randomize();
  fp = fopen("/www/my_c_lib/test/avl/generateData", "w");
  while(i<100000){
    n = RandomInteger(0, 1000000);
    if(FindAVLNode(avl, &n)==NULL){
      InsertAVLNode(avl, &n, NULL);
      fprintf(fp, "%-8d", n);
      num[i] = n;   
      i++;
    }
  }
  fclose(fp);

  /*temp = 7;
  DeleteAVLNode(avl, &temp);*/
  
  fp = fopen("/www/my_c_lib/test/avl/deleteData", "w");
  int j = 0;
  while(j < 90000){
    n = RandomInteger(0, 1000000);
    if(FindAVLNode(avl, &n)!=NULL){
      fprintf(fp, "%-8d", n);
      delptr = DeleteAVLNode(avl, &n);
      j++;
    }
  }
  fclose(fp);

  fp = fopen("/www/my_c_lib/test/avl/testInOrder", "w");
  if(fp == NULL) Error("Open file faile");
  MapAVL(write, avl, InOrder, fp);
  fclose(fp);

  fp = fopen("/www/my_c_lib/test/avl/testPreOrder", "w");
  if(fp == NULL) Error("Open file faile");
  MapAVL(write, avl, PreOrder, fp);
  fclose(fp);
}

void IntNodeInit(void *np, void *kp, void *clientData)
{
  *((int *)np) = *((int *)kp);
}

void display(void *np, void *clientData)
{
  int value;

  value = *(int *)np;
  printf("%d\n", value);
}
 
void write(void *np, void *fp)
{
  int value;
 
  value = *(int*)np;
  fprintf(fp, "%-8d", value);
}
