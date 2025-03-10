/*全排列II*/
#include <vector>
#include <unordered_set>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution{
private:
    vector<int> path;
    vector<vector<int>> result;
    void backtracking(const vector<int>& nums, vector<bool> used) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (i > 0 && (nums[i] == nums[i - 1] && used[i - 1] == false)) {
                continue;
            }
            if (used[i] == false) {
                used[i] = true;
                path.push_back(nums[i]);
                backtracking(nums, used);
                path.pop_back();
                used[i] = false;
            }
        }
    }
public:
    void permute(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return;
        sort(nums.begin(), nums.end());
        vector<bool> used(n, false);
        backtracking(nums, used);
    }

    void test() {
        for (auto vec : result) {
            for (auto number : vec) {
                cout << number << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    vector<int> input = {1, 1, 2, 3};
    Solution s;
    s.permute(input);
    s.test();
    return 0;
}