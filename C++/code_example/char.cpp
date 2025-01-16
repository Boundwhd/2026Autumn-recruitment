#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;


// test1 字符串存储在栈中
void test1(){
    char str[] = "abc";                
    //1. 栈中的字符串可以修改
    str[0] = 'w';
    cout << str << endl;

    char str1[] = "abcd";  
    char str2[] = "abce";  
    //2. 地址相同与字符串匹配
    cout << "地址：" << (str1 == str2) <<endl;
    // 字符串相同需要便利整个字符串，变量存放的是第一个字符的地址
    cout << "字符串数组第一个字符：" << (*str1 == *str2) <<endl;
}

// 字符串存储在常量区中
void test2(){

    //字符串常量在 C++ 中被定义为只读内存，而将它赋值给一个 char*，字符串无法修改
    const char* str = "abc";
    
    //输出字符串
    cout << str << endl;

    //输出指针地址
    cout << (void *)str << endl;

    //输出字符串的第一个字符（a）
    cout << *str << endl;


    // 字符串相等判断
    const char* str1 = "abb";
    const char* str2 = "abc";

    cout << (str1 == str2) << endl;
    cout << (*str1 == *str2) << endl;
    /*对于相同的字符串常量，系统会把他们优化，指向同一个内存区域*/
}

//
void test3(){
    //字符串存放在堆区
    char* str = (char*)malloc(5);
    const char* str1 = "abcd";

    //把str1的字符串复制到str中
    strcpy(str, str1);

    //比较地址是否相同
    cout << (str == str1) << endl;

}


int main(){

    test3();
    return 0;
}
