/*跳跃游戏*/
# include "../leetcode.h"

bool canJump(vector<int>& nums) {
        int max_dis = nums[0];
        for(int i = 1; i < nums.size(); i++){
            if(max_dis < i){
                return false;
            }else{
                max_dis = max(i + nums[i], max_dis);
            }
        }
        return true;
    }

/*
到达某个位置，先看能不能到这个位置；
不能到达这个位置就false，能到达这个位置，更新最远距离。
*/
