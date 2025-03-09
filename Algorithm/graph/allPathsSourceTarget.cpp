#include <vector>
using namespace std;

class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;
    void dfs(vector<vector<int>>& graph, int x, int n) {
        if (x == n) {
            result.push_back(path);
            return;
        }
        for (auto i : graph[x]) {
            path.push_back(i);
            dfs(graph, i, n);
            path.pop_back();
        }
    }
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
        int n = graph.size() - 1;
        path.push_back(0);
        dfs(graph, 0, n);
        return result;
    }
};