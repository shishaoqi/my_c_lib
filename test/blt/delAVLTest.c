/*
* @Author: shishao
* @Date:   2019-07-16 13:36:23
* @Last Modified by:   shishao
* @Last Modified time: 2019-07-19 17:36:23
*/

#include"genlib.h"
#include"cmpfn.h"
#include"blt.h"

void IntNodeInit(void *np, void *kp, void *clientData);
void display(void *np, void *clientData);
void write(void *np, void *clientData);
main()
{
  FILE *fp;
  int i=0, temp, second;
  int num[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  
  bstADT bst;

  bst = NewBST(sizeof(int), IntCmpFn, IntNodeInit);
  while(i<10){
    temp = num[i++];
    InsertBSTNode(bst, &temp, NULL);
  }

  /*temp = 167;
  InsertBSTNode(bst, &temp, NULL);
  */
  int j = 0;
  int n = 9;
  while(j++ < 3){
    second = num[n--];
    DeleteBSTNode(bst, &second);
  }

  fp = fopen("/www/my_c_lib/test/blt/testInOrder", "w");
  if(fp == NULL) Error("Open file faile");
  MapBST(write, bst, InOrder, fp);
  fp = fopen("/www/my_c_lib/test/blt/testPreOrder", "w");
  if(fp == NULL) Error("Open file faile");
  MapBST(write, bst, PreOrder, fp);
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
  fprintf(fp, "%-4d", value);
}
