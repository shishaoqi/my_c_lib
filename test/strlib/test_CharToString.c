#include <stdio.h>
#include "strlib.h"
#include "assert.h"

int main() {
    char c = 'a';
    string str;

    str = CharToString(c);
    printf("%s\n", str);
}