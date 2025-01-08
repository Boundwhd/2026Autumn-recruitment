#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;

int main(){

    char str1[] = "abc";                //字符串存储在栈中
    char str2[] = "abc";

    bool a = (*str1 == *str2);
    cout  << a << endl;
    str1[0] = 'b';
    cout << str1 << endl;

    // 字符串常量在 C++ 中被定义为 只读内存，而将它赋值给一个 char* 
    // 意味着你试图修改这块只读内存中的内容，这在现代 C++ 中是被禁止的。

    const char *str3 = "abc";         //字符串存储在常量区
    const char *str4 = "abc";
    printf("%p\n", (void *)str3);

    char *str5 = (char*)malloc(4);      //字符串存储在堆区
    strcpy(str5,str1);      
    a = (str5 == str1);
    cout << a << endl;

    char c = 'a';
    char b = 'a';

    a = (c == b);
    cout << a << endl;

    return 0;
}
