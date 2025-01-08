/*跳跃游戏II*/
# include "../leetcode.h"

int jump(vector<int>& nums) {
        int max_pos = 0;
        int end = 0;
        int ans = 0;
        for(int i = 0; i < nums.size() - 1; i++){
            max_pos = max(max_pos, i + nums[i]);
            if (i == end){
                end = max_pos;
                ans++;
            }
        }
        return ans;
    }

/*
算跳到最后一共经历了多少次区间，用end来计算区间边界，到达一次end，ans++
*/