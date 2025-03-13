#include <vector>
using namespace std;
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int total = 0;
        for (auto num : nums) {
            total += num;
        }

        if ((target > total) || (target + total) % 2 != 0) return 0;

        int sum_pos = (target + total) / 2;

        vector<int> dp(sum_pos + 1, 0);
        dp[0] = 1;

        for (auto num : nums) {
            for (int j = sum_pos; j >= num; j++) {
                dp[j] += dp[j - num];
            }
        }
        return dp[target];
    }
};