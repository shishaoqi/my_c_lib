#include"genlib.h"
#include"random.h"
#include"avl.h"

void IntNodeInit(void *np, void *kp, void *clientData);
//void display(void *np, void *clientData);
void write(void *np, void *fp);
void writeEnter(void *fp);

main()
{
  int array[100000]={0};
  avlADT avl;
  int value, i=0, n=0;
  FILE *fp;

  avl = NewAVL(sizeof(int), IntCmpFn, IntNodeInit);

  fp = fopen("/www/my_c_lib/test/avl/generateAVLData", "w");
  Randomize();
  while(i<10000){
    value = RandomInteger(1, 500000);
    if(FindAVLNode(avl, &value) == NULL){
      InsertAVLNode(avl, &value, NULL);
      fprintf(fp, "%-8d", value);
      array[i] = value;       
      i++;
    }
  }
  fclose(fp);

  fp = fopen("/www/my_c_lib/test/avl/deleteAVLData", "w");
  i=0;
  while(i<9970){
    n = RandomInteger(1, 500000);
    //严重的低级错误
    /*if(FindAVLNode(avl, &array[n])!=NULL){
      DeleteAVLNode(avl, &array[n]);
      fprintf(fp, "%-8d", &array[n]);
      i++;
    }*/
    if(FindAVLNode(avl, &n)!=NULL){
      DeleteAVLNode(avl, &n);
      fprintf(fp, "%-8d", n);
      i++;
    }
  }
  fclose(fp);

  fp = fopen("/www/my_c_lib/test/avl/random", "w");
  if(fp == NULL) Error("Open file faile");
  MapAVL(write, avl, InOrder, fp);
  writeEnter(fp);
  MapAVL(write, avl, PreOrder, fp);
  fclose(fp);

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
