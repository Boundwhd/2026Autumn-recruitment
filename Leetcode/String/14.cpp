/*最长公共前缀*/
#include "../leetcode.h"

string longestCommonPrefix(vector<string>& strs) {
    int m = strs[0].length();
    if(m == 0) return "";
    int n = strs.size();
    int i = 0;
    while(i < m) {
        char letter = strs[0][i];
        for (int j = 1; j < n; j++){
            if (i == strs[j].length() || strs[j][i] != letter){
                return strs[0].substr(0, i);
            }
        }
        i++;
    }
    return strs[0];
}

/*
拿出数组中第一个字符串，循环判断后面的字符串是否符合第一个字符串，两个终止条件
1）长度不够了
2）字符不等于第一个字符串的字
*/