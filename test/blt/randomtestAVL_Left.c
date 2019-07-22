#include"genlib.h"
#include"random.h"
#include"bst.h"

void IntNodeInit(void *np, void *kp, void *clientData);
//void display(void *np, void *clientData);
void write(void *np, void *fp);
void writeEnter(void *fp);

main()
{
  int array[10000]={0};
  bstADT bst;
  int value, i=0, n=0;
  FILE *fp;

  bst = NewBST(sizeof(int), IntCmpFn, IntNodeInit);

  Randomize();
  while(i<10000){
    value = RandomInteger(0, 50000);
    if(FindBSTNode(bst, &value) == NULL){
      InsertBSTNode(bst, &value, NULL);
      array[i] = value;       
      i++;
    }
  }

  i=0;
  while(i<9970){
    n = RandomInteger(0, 10000);
    if(FindBSTNode(bst, &array[n])!=NULL && array[n]>100){
      DeleteBSTNode(bst, &array[n]);
      i++;
    }
  }

  fp = fopen("/www/cProgram/abstract/chapter13/AVLtest/random2", "w");
  if(fp == NULL) Error("Open file faile");
  MapBST(write, bst, InOrder, fp);
  writeEnter(fp);
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
  fprintf(fp, "%-6d", value);
}

void writeEnter(void *fp)
{
  fputs("\n\n", fp);
}
