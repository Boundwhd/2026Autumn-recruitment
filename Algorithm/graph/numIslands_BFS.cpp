#include <vector>
#include <string>
#include <iostream>
#include <queue>
using namespace std;


class Solution{
private:
    int d_x[4] = {1, 0, -1, 0};
    int d_y[4] = {0, -1, 0, 1};
    void bfs(vector<vector<char>>&grid, int x, int y) {
        queue<pair<int, int>> q;
        q.push({x, y});

        while (!q.empty()) {
            pair<int, int> curr_pos = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int new_x = curr_pos.first + d_x[i];
                int new_y = curr_pos.second + d_y[i];
                if (new_x >= 0 && new_x < grid.size() && new_y >= 0 && new_y < grid[0].size() 
                    && grid[new_x][new_y] == '1') {
                        grid[new_x][new_y] = '0';
                        q.push({new_x, new_y});
                    }
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
                    grid[i][j] = '0';
                    result++;
                    bfs(grid, i, j);
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