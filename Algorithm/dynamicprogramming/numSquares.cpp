#include <vector>
using namespace std;

class Solution {
public:
    int numSquares(int n) {
        vector<int> dp(n + 1, __INT32_MAX__);
        
        dp[0] = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j * j <= i; j++) {
                dp[i] = min(dp[i], dp[i - j*j] + 1);
            }
        }
        return dp[n];
    }
};