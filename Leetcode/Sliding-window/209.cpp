/*长度最小的子数组*/
#include "../leetcode.h"

int minSubArrayLen(int target, vector<int>& nums) {
    int n = nums.size();
    int left = 0, sum = 0;
    int minLength = INT_MAX;

    for (int right = 0; right < n; right++) {
        sum += nums[right];

        while (sum >= target) {
            minLength = min(minLength, right - left + 1);
            sum -= nums[left];
            left++;
        }

    }
    return minLength == INT_MAX ? 0 : minLength;
}

int main(){
    vector<int> nums = {2, 3, 1, 2, 4, 3};
    int tar = 7;

    int ans = minSubArrayLen(tar, nums);
    return 0;
}