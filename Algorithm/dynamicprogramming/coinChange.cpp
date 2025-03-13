#include <vector>
using namespace std;
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, __INT_MAX__);
        dp[0] = 0;
        for (auto coin : coins) {
            for (int j = coin; j <= amount; j++) {
                if (dp[j - coin] != __INT_MAX__) {
                    dp[j] = min(dp[j], dp[j - coin] + 1);
                }
            }
        }
        return dp[amount] == __INT_MAX__ ? -1 : dp[amount];
    }
};