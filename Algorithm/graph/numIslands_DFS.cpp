#include <vector>
#include <string>
#include <iostream>
using namespace std;


class Solution{
private:
    int d_x[4] = {1, 0, -1, 0};
    int d_y[4] = {0, -1, 0, 1};
    void dfs(vector<vector<char>>&grid, int x, int y){
        grid[x][y] = '0';
        for (int ii = 0; ii < 4; ii++) {
            int new_x = x + d_x[ii];
            int new_y = y + d_y[ii];
            if (new_x >= 0 && new_y >= 0 && new_x < grid.size() && new_y < grid[0].size() 
                && grid[new_x][new_y] == '1') {
                    dfs(grid, new_x, new_y);
            }
        }
    }
public:
    int numIslands(vector<vector<char>>&grid) {
        int result = 0;
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    result++;
                    dfs(grid, i, j);
                }
            }
        }
        return result;
    }
};


int main() {
    int N = 0;
    int M = 0;
    cout << "输入岛屿行数目：";
    cin >> N;
    cout << "输入岛屿列数目：";
    cin >> M;

    vector<vector<char>> grid(N, vector<char>(M));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> grid[i][j];
        }
    }
    Solution s;
    int result = s.numIslands(grid);
    cout << result << endl;
    return 0;
}