/*赎金信*/
#include "../leetcode.h"

bool canConstruct(string ransomNote, string magazine) {
    unordered_map<char, int> hs;
    for (int i = 0; i < magazine.length(); i++) {
        hs[magazine[i]]++;
    }

    for (int i = 0; i < ransomNote.length(); i++) {
        if (hs[ransomNote[i]] <= 0) return false;
        hs[ransomNote[i]]--;
    }
    return true;
}