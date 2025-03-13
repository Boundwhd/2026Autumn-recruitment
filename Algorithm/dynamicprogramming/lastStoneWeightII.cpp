#include <vector>
using namespace std;

class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int total = 0;
        for (int i = 0; i < stones.size(); i++) {
            total += stones[i];
        }
        int target = total / 2;

        vector<int> dp(target + 1, 0);
        for (auto stone : stones) {
            for (int j = target; j >= stone; j--) {
                dp[j] = max(dp[j], dp[j - stone] + stone);
            }
        }
        return total - 2 * dp[target];
    }
};