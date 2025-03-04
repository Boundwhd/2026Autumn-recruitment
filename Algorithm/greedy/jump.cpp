#include <vector>
using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        if (nums.size() == 1) return 0;
        int curr_cover = 0;
        int next_cover = 0;
        int result = 0;
        for (int i = 0; i < nums.size(); i++) {
            next_cover = max(next_cover, nums[i] + i);
            if (i == curr_cover) {
                result++;
                curr_cover = next_cover;
                if (curr_cover >= nums.size() - 1) break;
            }
        }
        return result;
    }
};