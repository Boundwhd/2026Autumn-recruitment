/*存在重复元素II*/
#include "../leetcode.h"

bool containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_map<int, int> hs;
    for (int i = 0; i < nums.size(); i++) {
        if (hs.count(nums[i])) {
            if (abs(i - hs[nums[i]]) <= k) return true;
            else hs[nums[i]] = i;
        }else{
            hs[nums[i]] = i;
        }
    }       
    return false;
}