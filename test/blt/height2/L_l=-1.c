#include"genlib.h"
#include"cmpfn.h"
#include"blt.h"

void IntNodeInit(void *np, void *kp, void *clientData);
void display(void *np, void *clientData);
void write(void *np, void *clientData);
main()
{
  FILE *fp;
  int i=0,temp, second, three;
  int num[29] = {145, 58, 89, 4, 148, 72, 61, 141, 23, 136, 126, 52, 154, 33, 212, 221, 123, 68, 47, 111, 79, 53, 129, 121, 25, 174, 184, 32, 232};
  
  bstADT bst, findNode;

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

 
  second = 123;
  DeleteBSTNode(bst, &second);

  three = 145;
  findNode = FindBSTNode(bst, &three);
  BSTLeftChild(bst, findNode);



  fp = fopen("/www/my_c_lib/test/blt/height2/L=-1_In", "w");
  if(fp == NULL) Error("Open file faile");
  MapBST(write, bst, InOrder, fp);
  fp = fopen("/www/my_c_lib/test/blt/height2/L=-1_Pre", "w");
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
