/*盛水最多的容器*/
#include "leetcode.h"

int maxArea(vector<int>& height) {
    int left = 0;
    int right = height.size()-1;

    int max_water = 0;
    while(left < right){
        max_water = max(max_water, min(height[left], height[right]) * (right - left));
        if (height[left] < height[right]){
            left++;
        } else {
            right--;
        }
    }
    return max_water;
}
/*双指针*/