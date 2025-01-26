/*有效的字母异位词*/
#include "../leetcode.h"

bool isAnagram(string s, string t) {
    if (s.length() != t.length()) return false;

    unordered_map<char, int> ht;
    for (int i = 0; i < s.length(); i++) {
        ht[s[i]]++;
    }

    for (int i = 0; i < t.length(); i++) {
        if (ht[t[i]] <= 0) return false;
        ht[t[i]]--;
    } 

    return true;
}