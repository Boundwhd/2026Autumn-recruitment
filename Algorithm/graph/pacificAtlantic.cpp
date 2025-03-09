#include <vector>
using namespace std;

class Solution {
private:
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    vector<vector<int>> result;
    void dfs(vector<vector<int>> &height, vector<vector<bool>> &visited, int x, int y){
        visited[x][y] = true;
        for (int i = 0; i < 4; i++) {
            int xx = x + dx[i];
            int yy = y + dy[i];
            if (xx >= 0 && yy >= 0 && xx < height.size() && yy < height[0].size() && visited[xx][yy] == false && height[xx][yy] >= height[x][y] ) {
                dfs(height, visited, xx, yy);
            } 
        }
        return;
    }

public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int m = heights.size();
        int n = heights[0].size();
        vector<vector<bool>> visited_1(m, vector<bool>(n, false));
        vector<vector<bool>> visited_2(m, vector<bool>(n, false));


        for (int i = 0; i < n; i++) {
            dfs(heights, visited_1, 0, i);
            dfs(heights, visited_2, m - 1, i);
        }
        
        for (int i = 0; i < m; i++) {
            dfs(heights, visited_1, i, 0);
            dfs(heights, visited_2, i, n - 1);
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (visited_1[i][j] && visited_2[i][j]) {
                    result.push_back({i, j});
                }
            }
        }
        return result;
    }
};