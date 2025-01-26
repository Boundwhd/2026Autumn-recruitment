/*同构字符串*/

#include "../leetcode.h"

bool isIsomorphic(string s, string t) {
    unordered_map<char, char> hs;
    unordered_map<char, char> ht;
    for (int i = 0; i < s.length(); i++) {
        if (!hs.count(s[i]) && !ht.count(t[i])) {
            hs[s[i]] = t[i];
            ht[t[i]] = s[i];
        }

        if (hs[s[i]] != t[i] || ht[t[i]] != s[i]) {
            return false;
        }
    }   
    return true;
}

/*双哈希表*/