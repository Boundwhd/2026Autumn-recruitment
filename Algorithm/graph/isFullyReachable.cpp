#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

void dfs(vector<vector<int>>& graph, int node, unordered_set<int>& final_visited) {
    if (!final_visited.count(node)) {
        final_visited.insert(node);
    }
    for (auto i : graph[node]) {
        if (!final_visited.count(i)) {
            dfs(graph, i, final_visited);
        }
    }
}

bool isFullyReachable(vector<vector<int>>& graph) {
    int target_num = graph.size() - 1;
    unordered_set<int> final_visited;
    final_visited.insert(1);
    dfs(graph, 1, final_visited);
    return final_visited.size() == target_num;
}

int main() {
    vector<vector<int>> graph = {{}, {2}, {5}, {}, {3, 5}, {4}, {7, 8}, {8}, {}};
    
    bool K = isFullyReachable(graph);

    cout << K << endl;

    return 0;
}