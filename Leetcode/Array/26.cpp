/*删除有序数组重复项*/
#include "../leetcode.h"

int removeDuplicates(vector<int>& nums) {
        if (nums.size() < 2) return nums.size();
        int idx = 0;
        for (int i = 1; i < nums.size(); i++){
            if(nums[i] != nums[idx]){
                nums[++idx] = nums[i];
            }
        }
        return idx + 1;
    }

/*
双指针，一个指针遍历数组，另一个指针指向第一个不重复元素。
如果有第二个不重复元素，把他加入到idx++的位置。
*/

