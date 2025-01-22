/*最小覆盖子串*/
#include "../leetcode.h"

string minWindow(string s, string t){
    unordered_map<char, int> ht, hs;
    string ans;
    for (auto c : t){
        ht[c]++;
    }

    for (int i = 0, j = 0, cnt = 0; i < s.length(); i++) {
        if (++hs[s[i]] <= ht[s[i]]) cnt++;

        while (hs[s[j]] > ht[s[j]]) hs[s[j++]]--;

        if (cnt == t.length()) {
            if (ans.empty() || ans.length() > i - j + 1) {
                ans = s.substr(j, i - j + 1);
            }
        }
    }
    return ans;
}