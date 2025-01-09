/*最后一个单词的长度*/

#include "../leetcode.h"
int lengthOfLastWord(string s) {
        int n = s.length();
        int i = n - 1;

        while(i >= 0 && s[i] == ' '){
            i--;
        }

        int length = 0;
        while(i >= 0 && s[i] != ' '){
            length++;
            i--;
        }
        return length;
    }

/*
去掉尾部空格：

我们从字符串的末尾开始，使用 while (i >= 0 && s[i] == ' ') 跳过尾部的空格字符。
计算最后一个单词的长度：

接下来，我们继续从当前位置往前走，直到遇到空格为止，在此过程中，计数器 length 用来记录最后一个单词的长度。
返回长度：

最终返回计算出的 length，即最后一个单词的长度。
*/