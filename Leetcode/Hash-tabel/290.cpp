/*单词规律*/

#include "../leetcode.h"

bool wordPattern(string pattern, string s) {
    unordered_map<char, string> hs;
    unordered_map<string, char> hp;
    int start = 0;
    int i = 0;
    int j = 0;
    while (i < s.length()) {
        if (j == s.length())
            return false;
        if ((s[i] == ' ') || (i == s.length() - 1)) {
            string word = (i == s.length() - 1)
                                ? s.substr(start, i - start + 1)
                                : s.substr(start, i - start);
            if (hs.count(pattern[j]) && hs[pattern[j]] != word)
                return false;
            if (hp.count(word) && hp[word] != pattern[j])
                return false;
            hs[pattern[j]] = word;
            hp[word] = pattern[j];
            start = i + 1;
            j++;
        }
        i++;
    }
    return j == pattern.length() ? true : false;
}


/*如何按照空格获取单词？*/