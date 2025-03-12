#include <vector>
using namespace std;
class Solution {
    public:
        bool canPartition(vector<int>& nums) {
            int target = 0;
            for (int i = 0; i < nums.size(); i++) {
                target += nums[i];
            }
            if (target % 2 == 1) return false; // 如果总和是奇数，直接返回 false
            target /= 2; // 目标值是总和的一半
    
            // dp[i][j] 表示前 i 个物品中能否选出一些物品，使得它们的总和等于 j
            vector<vector<bool>> dp(nums.size() + 1, vector<bool>(target + 1, false));
    
            // 初始化：当目标值为 0 时，总是可以选出空集
            for (int i = 0; i <= nums.size(); i++) {
                dp[i][0] = true;
            }
    
            // 动态规划填充 dp 数组
            for (int i = 1; i <= nums.size(); i++) {
                for (int j = 1; j <= target; j++) {
                    if (nums[i - 1] > j) {
                        dp[i][j] = dp[i - 1][j]; // 不能选当前物品
                    } else {
                        dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]]; // 选或不选当前物品
                    }
                }
                // 如果已经找到满足条件的子集，直接返回 true
                if (dp[i][target]) {
                    return true;
                }
            }
    
            return false;
        }
    };