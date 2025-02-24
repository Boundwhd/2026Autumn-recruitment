/*除法求值*/
#include "../leetcode.h"

class Solution {
    public:
        // 使用哈希表来存储图
        unordered_map<string, unordered_map<string, double>> graph;
    
        // 构建图
        void buildGraph(const vector<vector<string>>& equations, const vector<double>& values) {
            for (int i = 0; i < equations.size(); i++) {
                const string& a = equations[i][0];
                const string& b = equations[i][1];
                double value = values[i];
                
                graph[a][b] = value;
                graph[b][a] = 1.0 / value;
            }
        }
    
        // DFS 搜索
        double dfs(const string& start, const string& end, unordered_set<string>& visited) {
            if (graph.find(start) == graph.end() || graph.find(end) == graph.end()) {
                return -1.0;  // 如果没有这个节点，返回-1.0
            }
    
            if (start == end) {
                return 1.0;
            }
    
            visited.insert(start);
    
            for (auto& neighbor : graph[start]) {
                const string& next = neighbor.first;
                double val = neighbor.second;
    
                if (visited.find(next) == visited.end()) {
                    double result = dfs(next, end, visited);
                    if (result != -1.0) {
                        return result * val;
                    }
                }
            }
    
            return -1.0;
        }
    
        vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
            // 构建图
            buildGraph(equations, values);
    
            vector<double> result;
    
            // 对每个查询进行处理
            for (auto& query : queries) {
                const string& start = query[0];
                const string& end = query[1];
    
                unordered_set<string> visited;
                result.push_back(dfs(start, end, visited));
            }
    
            return result;
        }
    };