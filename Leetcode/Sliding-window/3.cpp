/*无重复字符的最长子串*/
#include "../leetcode.h"

int lengthOfLongestSubstring(string s) {
    int left = 0;
    int max_length = 0;
    unordered_map<char, int> hash;

    for (int right = 0; right < s.length(); right++) {
        if (!hash.count(s[right])) {
            hash[s[right]] = 1;
            max_length = max(max_length, right - left + 1);
        } else {
            while (hash.count(s[right])) {
                hash.erase(s[left]);
                left++;
            }
            hash[s[right]] = 1;
        }
    }
    return max_length;
}