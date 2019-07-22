#include"genlib.h"
#include"cmpfn.h"
#include"blt.h"

void IntNodeInit(void *np, void *kp, void *clientData);
void display(void *np, void *clientData);
void write(void *np, void *clientData);
main()
{
  FILE *fp;
  int i=0,temp, second;
  int num[29] = {145, 58, 89, 4, 148, 72, 61, 141, 23, 136, 126, 52, 154, 33, 212, 221, 123, 68, 47, 111, 79, 53, 129, 121, 25, 174, 184, 32, 232};
  
  bstADT bst;

  bst = NewBST(sizeof(int), IntCmpFn, IntNodeInit);
  while(i<29){
    temp = num[i++];
    InsertBSTNode(bst, &temp, NULL);
  }

  temp = 167;
  InsertBSTNode(bst, &temp, NULL);
  temp = 142;
  InsertBSTNode(bst, &temp, NULL);
  temp = 150;
  InsertBSTNode(bst, &temp, NULL);
  temp = 93;
  InsertBSTNode(bst, &temp, NULL);
  temp = 27;
  InsertBSTNode(bst, &temp, NULL);
  temp = 29;
  InsertBSTNode(bst, &temp, NULL);
  temp = 116;
  InsertBSTNode(bst, &temp, NULL);

  second = 167;
  DeleteBSTNode(bst, &second);
 

  fp = fopen("/www/my_c_lib/test/blt/height2/L=1", "w");
  if(fp == NULL) Error("Open L=1 file faile");
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
