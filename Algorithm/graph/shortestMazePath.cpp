#include <vector>
#include <queue>
#include <iostream>
using namespace std;

class Solution {
private:
    int result;
    int d_x[4] = {0, 1, 0, -1};
    int d_y[4] = {-1, 0, 1, 0};
public:
    int bfs(vector<vector<int>>& grid, int x, int y, int terminal_x, int terminal_y) {
        vector<vector<bool>> visited(terminal_x, vector<bool>(terminal_y));
        queue<pair<int, int>> q;
        queue<int> step;

        q.push({x, y});
        step.push(0);
        visited[x][y] = true;

        while(!q.empty()) {
            int curr_x = q.front().first;
            int curr_y = q.front().second;
            int cur_step = step.front();
            q.pop();
            step.pop();

            if (curr_x == terminal_x - 1 && curr_y == terminal_y - 1) {
                return cur_step;
            }

            for (int i = 0; i < 4; i++) {
                int new_x = curr_x + d_x[i];
                int new_y = curr_y + d_y[i];

                if (new_x >= 0 && new_x < terminal_x && new_y >= 0 && new_y < terminal_y 
                    && grid[new_x][new_y] != 1 && visited[new_x][new_y] == false) {
                        q.push({new_x, new_y});
                        step.push(cur_step + 1);
                        visited[new_x][new_y] = true;
                }   
            }
        }
        return -1;
    }
    int shortestMazePath(vector<vector<int>>& grid) {
        int terminal_x = grid.size();
        int terminal_y = grid[0].size();

        return bfs(grid, 0, 0, terminal_x, terminal_y);
    }
};

int main() {
    Solution sol;
    vector<vector<int>> maze = {
        {0, 0, 1, 0},
        {1, 0, 1, 0},
        {0, 0, 0, 0},
        {1, 1, 0, 0}
    };
    std::cout << "最短路径步数: " << sol.shortestMazePath(maze) << std::endl;
    return 0;
}