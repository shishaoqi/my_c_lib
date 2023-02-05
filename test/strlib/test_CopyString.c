#include <stdio.h>
#include "strlib.h"
#include "assert.h"

int main() {
    string src, cpy;

    src = "source string";
    cpy = CopyString(src);

    printf("copy string: %s\n", cpy);

    CopyString(NULL);
}