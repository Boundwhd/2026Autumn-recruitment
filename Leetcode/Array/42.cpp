/*接雨水*/
#include "../leetcode.h"

int trap(vector<int>& height) {
        vector<int> left(height.size(), 0);
        vector<int> right(height.size(), 0);
        int max_left = height[0];
        int max_right = height[height.size() - 1];
        int ans = 0;
        for (int i = 1; i < height.size(); i++) {
            left[i] = max_left;
            max_left = max(max_left, height[i]);
        }
        for (int i = height.size() - 2; i >= 0; i--) {
            right[i] = max_right;
            max_right = max(max_right, height[i]);
        }
        for(int i = 0;i < height.size(); i++){
            ans += max(min(left[i], right[i]) - height[i], 0);
        }
        return ans;
    }

/*用两个数组，分别存放他左边的最大值和右边的最大值，最后取小的最大值减去自己的height即可*/