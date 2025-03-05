#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
private:
    vector<int> path;
    vector<vector<int>> result;
    void backtracking(vector<int>& nums, int startIndex) {
        if (path.size() >= 2 ) {
            result.push_back(path);
        }
        unordered_set<int> used;
        for (int i  = startIndex; i < nums.size(); i++) {
            if (!path.empty() && nums[i] < path.back() || used.find(nums[i]) != used.end()) {
                continue;
            }
            used.insert(nums[i]);
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        backtracking(nums, 0);
        return result;
    }
};