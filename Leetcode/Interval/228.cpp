/*汇总区间*/
#include "../leetcode.h"

vector<string> summaryRanges(vector<int>& nums) {
    int start = 0;
    vector<string> ans;
    if (nums.empty()) return ans;

    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] != nums[i - 1] + 1) {
            if (i - start == 1) {
                ans.push_back(to_string(nums[start]));
            } else {
                ans.push_back(to_string(nums[start]) + "->" + to_string(nums[i - 1]));
            }
            start = i;
        }
    }
    
    if (start == nums.size() - 1) {
        ans.push_back(to_string(nums[start]));
    } else {
        ans.push_back(to_string(nums[start]) + "->" + to_string(nums.back()));
    }

    return ans;
}