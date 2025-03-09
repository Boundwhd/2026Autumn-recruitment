// -------ACM模式
// 1. 邻接矩阵存储
// 2. leetocde 模式
#include <vector>
#include <iostream>
using namespace std;

class Solution{
private:
    vector<vector<int>> result;
    vector<int> path;
    void dfs(vector<vector<int>>& graph, int x, int n) {
        if (x == n) {
            result.push_back(path);
            return;
        }
        for (int i = 1; i <= n; i++) {
            if (graph[x][i] == 1) {
                path.push_back(i);
                dfs(graph, i, n);
                path.pop_back();
            }
        }
    }
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph, int n) {
        path.push_back(1);
        dfs(graph, 1, n);
        return result;
    }
};



int main() {
    int n = 5; // 节点数量
    vector<vector<int>> graph(n+1, vector<int>(n+1, 0));
    graph[1][2] = 1;
    graph[2][4] = 1;
    graph[1][3] = 1;
    graph[3][5] = 1;
    graph[4][5] = 1;

    Solution s;
    vector<vector<int>> ans = s.allPathsSourceTarget(graph, n);
    if (ans.empty()) return 0;
    for (int i = 0; i < ans.size(); i++) {
        for (int j = 0; j < ans[i].size(); j++) {
            if (j == ans[i].size() - 1) {
                cout << ans[i][j] << endl;
            } else {
                cout << ans[i][j] << ' ';
            }
        }
    }
    return 0;
}
