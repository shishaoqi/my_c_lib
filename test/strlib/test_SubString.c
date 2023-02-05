#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "genlib.h"
#include "strlib.h"

int main() {
    string str, subStr, s2, s3, s4;

    str = "abcdefghijklmg";
    subStr = SubString(str, 1, 3);

    assert(strcmp(subStr, "bcd") == 0);
    printf("subString: %s\n", subStr);

    s2 = SubString(str, 5, 1);
    printf("SubString(str, 5, 1): %s\n", s2);
    assert(strcmp(s2, "") == 0);

    s3 = SubString(str, -3, 3);
    printf("s3: %s\n", s3);
    assert(strcmp(s3, "abcd") == 0);


    s4 = SubString(NULL, -3, 3);
}