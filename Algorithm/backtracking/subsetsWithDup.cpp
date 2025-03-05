#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
private:
    vector<int> path;
    vector<vector<int>> result;
    void backtracking(vector<int>& nums, int startIndex) {
        result.push_back(path);
        unordered_set<int> used;
        for(int i = startIndex; i < nums.size(); i++) {
            if (used.find(nums[i]) != used.end()) {
                continue;
            }
            used.insert(nums[i]);
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        backtracking(nums, 0);
        return result;
    }
};