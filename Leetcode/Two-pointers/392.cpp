/*判断子序列*/
#include "../leetcode.h"

bool isSubsequence(string s, string t) {
        int m = s.length();
        int n = t.length();
        if (m > n) return false;
        if (m == 0) return true;
        
        int i = 0;
        int j = 0;
        while(i < n){
            if(t[i] == s[j]){
                i++;
                j++;
                if (j == m) return true;
            }else{
                i++;
            }
        }
        return false;
    }

/*
该算法通过双指针的方式有效地检查一个字符串是否是另一个字符串的子序列。
它只需要遍历字符串 t 一次，时间复杂度为 O(n)，因此效率较高。
*/