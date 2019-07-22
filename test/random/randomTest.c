/*
* @Author: shishao
* @Date:   2019-07-23 00:10:06
* @Last Modified by:   shishao
* @Last Modified time: 2019-07-23 00:17:45
*/

#include <stdio.h>
#include "genlib.h"

int main() {
    FILE *fp;
    int n, i;

    fp = fopen("/www/my_c_lib/test/random/generateInt", "w");
    while(i<10000){
        n = RandomInteger(0, 100000);
          fprintf(fp, "%-8d", n);  
          i++;
    }
    fclose(fp);

    return 0;
}