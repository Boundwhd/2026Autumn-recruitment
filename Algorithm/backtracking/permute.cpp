#include <vector>
using namespace std;

class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> used;
    void backtracking(const vector<int>& nums, vector<bool> used) {
        if (nums.size() == path.size()) {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++) {
            if (used[i] == false) {
                path.push_back(nums[i]);
                used[i] = true;
                backtracking(nums, used);
                used[i] = false;
                path.pop_back();
            } else {
                continue;
            }
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<bool> used(nums.size(), false);
        backtracking(nums, used);
        return result;
    }
};