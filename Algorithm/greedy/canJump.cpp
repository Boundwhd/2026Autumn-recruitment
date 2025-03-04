#include <vector>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int cover = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (cover >= nums.size() - 1) {
                return true;
            } else if (cover >= i){
                cover = max(cover, nums[i] + i);
            } else {
                if (i != nums.size() - 1) break;
            }
            
        }
        return false;
    }
};