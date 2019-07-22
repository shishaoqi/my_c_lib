#include"genlib.h"
#include"cmpfn.h"
#include"bst.h"

void IntNodeInit(void *np, void *kp, void *clientData);
void display(void *np, void *clientData);
void write(void *np, void *clientData);
main()
{
  FILE *fp;
  int i=0,temp, second;
  int num[50] = {145, 95, 58, 132, 89, 93, 4, 183, 242, 148, 155, 72, 81, 61, 199, 141, 23, 21, 136, 129, 52, 99, 154, 150, 33, 212, 27, 221, 66, 123, 68, 142, 29, 116, 47, 207, 111, 79, 53, 143, 37, 129, 121, 25, 174, 184, 32, 15, 232, 167};
  
  bstADT bst;

  bst = NewBST(sizeof(int), IntCmpFn, IntNodeInit);
  while(i<50){
    temp = num[i++];
    InsertBSTNode(bst, &temp, NULL);
  }

  second = 121;
  DeleteBSTNode(bst, &second);

  second = 136;
  DeleteBSTNode(bst, &second);
  second = 143;
  DeleteBSTNode(bst, &second);
  second = 142;
  DeleteBSTNode(bst, &second);
  second = 145;
  DeleteBSTNode(bst, &second);

  fp = fopen("/savefile/abstract/chapter13/AVLtest/height3/L==0/l7", "w");
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
