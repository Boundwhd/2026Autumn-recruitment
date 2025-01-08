/*移除元素*/
# include "../leetcode.h"

int removeElement(vector<int>& nums, int val) {
        int j = 0;
        for(int i = 0; i < nums.size(); i++){
            if (nums[i] != val){
                nums[j] = nums[i];
                j++;
            }
        }
        return j;
    }


/*双指针，同时指在第一个，如果是慢指针不动，如果不是，快指针赋值给慢指针*/