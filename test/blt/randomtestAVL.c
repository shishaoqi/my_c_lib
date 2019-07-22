#include"genlib.h"
#include"random.h"
#include"blt.h"

void IntNodeInit(void *np, void *kp, void *clientData);
//void display(void *np, void *clientData);
void write(void *np, void *fp);
void writeEnter(void *fp);

main()
{
  int array[100000]={0};
  bstADT bst;
  int value, i=0, n=0;
  FILE *fp;

  bst = NewBST(sizeof(int), IntCmpFn, IntNodeInit);

  Randomize();
  while(i<100000){
    value = RandomInteger(0, 500000);
    if(FindBSTNode(bst, &value) == NULL){
      InsertBSTNode(bst, &value, NULL);
      array[i] = value;       
      i++;
    }
  }

  i=0;
  while(i<99970){
    n = RandomInteger(0, 100000);
    if(FindBSTNode(bst, &array[n])!=NULL){
      DeleteBSTNode(bst, &array[n]);
      i++;
    }
  }

  fp = fopen("/www/my_c_lib/test/blt/random1", "w");
  if(fp == NULL) Error("Open file faile");
  MapBST(write, bst, InOrder, fp);
  writeEnter(fp);
  MapBST(write, bst, PreOrder, fp);

}

void IntNodeInit(void *np, void *kp, void *clientData)
{
  *((int*)np) = *((int *)kp);
}

 
void write(void *np, void *fp)
{
  int value;
 
  value = *(int*)np;
  fprintf(fp, "%-8d", value);
}

void writeEnter(void *fp)
{
  fputs("\n\n", fp);
}
