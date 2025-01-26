/*字母异位词分组*/
#include "../leetcode.h"

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> hs;
    for (int i = 0; i < strs.size(); i++) {
        string key = strs[i];
        sort(key.begin(), key.end());
        hs[key].push_back(strs[i]);
    }

    vector<vector<string>> ans;
    for (auto i : hs) {
        ans.push_back(i.second);
    }        

    return ans;
}   