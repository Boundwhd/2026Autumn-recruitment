/*找出字符串中第一个匹配项下标*/
#include "../leetcode.h"

// 计算部分匹配表（LPS 表）
vector<int> computeLPS(const string& pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0); // 初始化 LPS 表
    int length = 0;        // 当前最长前缀后缀的长度
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1]; // 回退到之前的部分匹配位置
            } else {
                lps[i] = 0; // 没有匹配，设置为 0
                i++;
            }
        }
    }
    return lps;
}

int strStr(const string& haystack, const string& needle) {
    int n = haystack.size();
    int m = needle.size();

    if (m == 0) return 0; // 空模式串匹配在第一个位置
    if (n < m) return -1; // 主串长度小于模式串，无法匹配

    vector<int> lps = computeLPS(needle);
    int i = 0; // 主串指针
    int j = 0; // 模式串指针

    while (i < n) {
        if (haystack[i] == needle[j]) {
            i++;
            j++;
        }
        if (j == m) {
            // 匹配成功，返回起始位置
            return i - j;
        } else if (i < n && haystack[i] != needle[j]) {
            // 匹配失败，根据 LPS 表跳转
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return -1; // 未找到匹配
}

int main(){
    string a = "mississippi";
    string b = "ababa";
    int ans = strStr(a, b);
    return 0;
}