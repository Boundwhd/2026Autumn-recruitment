/*除自身以外的元素*/
#include "../leetcode.h"

vector<int> productExceptSelf(vector<int>& nums) {
    vector<int> left(nums.size(), 1);
    vector<int> right(nums.size(), 1);
    for(int i = 1; i < nums.size(); i++){
        left[i] = nums[i - 1] * left[i - 1];
    }
    for(int i = nums.size() - 2; i >= 0; i--){
        right[i] = nums[i + 1] * right[i + 1];
    }
    for(int i = 0; i < nums.size(); i++){
        right[i] = right[i] * left[i];
    }
    return right;
}

/*
用一个数组存放每个数字左边的累乘，乘上另一数组存他右边的累乘
*/