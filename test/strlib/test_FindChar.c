#include <stdio.h>
#include "strlib.h"
#include "assert.h"

int main() {
    char c = 'd';
    string s = "abcdefg";
    int idx;

    idx = FindChar(c, s, 7);
    printf("%c's index is %d in %s\n", c, idx, s);
}