#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    static bool cmp(int a, int b) {
        return abs(a) > abs(b);
    }
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end(), cmp);
        for (int i = 0 ; i < nums.size(); i++) {
            if (k == 0) break;
            if (nums[i] < 0 ) {
                nums[i] *= -1;
                --k;
            } 
        }
        if (k % 2 == 1) nums[nums.size() - 1] *= -1;
        int result = 0;
        for (auto i : nums) {
            result += i;
        }
        return result;
    }
};