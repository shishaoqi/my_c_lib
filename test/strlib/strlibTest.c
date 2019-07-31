/*
* @Author: shishao
* @Date:   2019-07-24 19:26:20
* @Last Modified by:   shishao
* @Last Modified time: 2019-07-25 00:00:59
*/

#include <stdio.h>
#include "strlib.h"

int main() {
    /*
     * Function: Concat
     * Usage: s = Concat(s1, s2);
     */
    string s = Concat("ABC", "DE");
    printf("%s\n", s);

    /*
     * Function: IthChar
     * Usage: ch = IthChar(s, i);
     * -------------------------------
     * IthChar(s, i) is like selecting s[i]
     */
    int index = 1;
    char reChar = IthChar(s, index);
    printf("%c\n", reChar);

    /*
     * Function: SubString
     * Usage: t = SubString(s, p1, p2);
     */
    string subStr = SubString(s, 0, 2);
    printf("%s\n", subStr);

    /*
     * Function: CharToString
     * Usage: s = CharToString(ch);
     */
    s = CharToString('A');
    printf("a one-character string: %s\n", s);

    /*
     * Function: StringLength
     * Usage: len = StringLength(s);
     */
    int len = StringLength(s);
    printf("This function returns the length of s: %d\n", len);

    /*
     * Function: CopyString
     * Usage: newstr = CopyString(s);
     */
    string newstr = CopyString("copy string");
    printf("a copy string: %s\n", newstr);

    /*
     * Function: StringEqual
     * Usage: if (StringEqual(s1, s2)) ...
     */
    string s1 = "abc";
    string s2 = "abc";
    bool flag = StringEqual(s1, s2);
    printf("bool = %d\n", flag);

    /*
     * Function: StringCompare
     * Usage: if (StringCompare(s1, s2) < 0) ...
     */
    

    return 0;
}