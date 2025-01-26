/*两数之和*/
#include "../leetcode.h"

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int ,int> hs;
    for (int i = 0;i < nums.size(); i++) {
        if (hs.count(nums[i])) return {hs[nums[i]], i};
        hs[target - nums[i]] = i;
    }
    return {0, 0};        
}