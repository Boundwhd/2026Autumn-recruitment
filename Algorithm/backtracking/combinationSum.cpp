#include <vector>
#include <algorithm>
using namespace std;
class Solution {
private:
    vector<int> path;
    vector<vector<int>> result;
    void backtracking(vector<int>& candidates, int sum, int startIndex, int target) {
        if (sum > target) return;
        if (sum == target) {
            result.push_back(path);
            return;
        }
        for (int i = startIndex; i < candidates.size() && sum + candidates[i] <= target; i++) {
            path.push_back(candidates[i]);
            sum += candidates[i];
            backtracking(candidates, sum, i, target);
            sum -= candidates[i];
            path.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        backtracking(candidates, 0, 0, target);
        return result;
    }
};

int main() {
    vector<int> candidate = {2, 3, 6, 7};
    int target = 7;
    Solution s;
    vector<vector<int>> a = s.combinationSum(candidate, 7);
    return 0;
}



