/*全排列I*/
#include <vector>
#include <unordered_set>
#include <iostream>
using namespace std;

class Solution{
private:
    vector<int> path;
    vector<vector<int>> result;
    void backtracking(const vector<int>& nums, unordered_set<int> used) {
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (!used.count(nums[i])) {
                path.push_back(nums[i]);
                used.insert(nums[i]);
                backtracking(nums, used);
                used.erase(nums[i]);
                path.pop_back();
            }
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return {};
        if (n == 1) return {{nums[0]}};

        unordered_set<int> used;
        backtracking(nums, used);
        return result;
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