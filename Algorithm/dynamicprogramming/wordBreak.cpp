#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;

        for (int i = 0; i <= s.size(); ++i) {
            if (!dp[i]) continue; // 如果 dp[i] 为 false，跳过
    
            for (const string& word : wordSet) {
                if (i + word.size() > s.size()) continue; // 如果 word 太长，跳过
    
                if (s.substr(i, word.size()) == word) {
                    dp[i + word.size()] = true;
                }
            }
        }
    }
};