#include <vector>
#include <algorithm>
using namespace std;
class Solution {
private:
    vector<int> path;
    vector<vector<int>> result;
    void backtracking(vector<int>& candidate, int target, int sum, int IndexStart, vector<bool>& used){
        if (sum == target) {
            result.push_back(path);
            return;
        }
        for (int i = IndexStart; i < candidate.size() && sum + candidate[i] <= target; i++) {
            if (i > 0 && candidate[i] == candidate[i - 1] && used[i - 1] == false) {
                continue;
            }
            path.push_back(candidate[i]);
            sum += candidate[i];
            used[i] = true;
            backtracking(candidate, target, sum, i + 1, used);
            used[i] = false;
            sum -= candidate[i];
            path.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<bool> used(candidates.size(), false);
        sort(candidates.begin(), candidates.end());
        backtracking(candidates, target, 0, 0, used);
        return result;
    }
};

int main() {

}