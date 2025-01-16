/*三数之和*/
#include "leetcode.h"

vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        int n = nums.size();

        sort(nums.begin(), nums.end());

        for (int i = 0; i < n - 2; i++) {
            //跳过重复元素
            if (i > 0 && nums[i] == nums[i - 1]){
                continue;
            }

            int left = i + 1;
            int right = n - 1;

            while(left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum == 0) {
                    result.push_back({nums[i], nums[left], nums[right]});

                    while (left < right && nums[left] == nums[left + 1]){
                        left++;
                    }
                    while (left < right && nums[right] == nums[right - 1]){
                        right--;
                    }

                    left++;
                    right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        return result;
    }

/*
解释：
排序：先对数组进行排序。排序后，双指针法可以更容易地判断和是否为0，同时可以避免重复三元组。
跳过重复的元素：如果当前元素和前一个元素相同，则跳过，避免重复计算相同的三元组。
双指针：对于每个 nums[i]，使用双指针从 i + 1 和数组末尾开始查找合适的 nums[j] 和 nums[k]。
当 nums[i] + nums[j] + nums[k] == 0 时，记录当前的三元组。如果三者和小于0，左指针右移；如果和大于0，右指针左移。
*/