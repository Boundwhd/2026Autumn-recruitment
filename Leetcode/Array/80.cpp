/*删除有序数组重复项*/
#include "../leetcode.h"

int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 2) return nums.size();
        int idx = 1;
        for (int i = 2; i < nums.size(); i++){
            if(nums[i] != nums[idx - 1]){
                nums[++idx] = nums[i];
            }
        }
        return idx + 1;
    }

/*
双指针，一个指针遍历数组，另一个指针指向第二个不重复元素。
和26类似的思路，具体看26题。关键点，慢指针+1等于新数字。
*/