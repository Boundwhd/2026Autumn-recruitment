#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;
class Solution {
private:
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    void dfs(vector<vector<int>>& grid, const int &mark, int &count, int x, int y) {
        count++;
        grid[x][y] = mark;
        for (int i = 0; i < 4; i++) {
            int xx = x + dx[i];
            int yy = y + dy[i];
            if (xx >= 0 && yy >= 0 && xx < grid.size() && yy < grid[0].size() && grid[xx][yy] == 1) {
                dfs(grid, mark, count, xx, yy);
            }
        }
    }
public:
    int largestIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int mark = 2; //岛屿标记
        bool all_Island = true;
        unordered_map<int, int> numIsland;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int count = 0; //记录当前岛屿数量
                if (grid[i][j] == 0) all_Island = false;
                if (grid[i][j] == 1) {
                    dfs(grid, mark, count, i, j);
                }
                numIsland[mark] = count;
                mark++;
            }
        }
        if (all_Island) return numIsland[2];
        unordered_set<int> Island_set;
        int result = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int total_area = 1;
                if (grid[i][j] == 0) {
                    Island_set.clear();
                    for (int k = 0; k < 4; k++) {
                        int ii = i + dx[k];
                        int jj = j + dy[k];
                        if (ii >=0 && jj >= 0 && ii < m && jj < n) {
                            if (grid[ii][jj] != 0 && Island_set.find(grid[ii][jj]) == Island_set.end()) {
                                Island_set.insert(grid[ii][jj]);
                                total_area += numIsland[grid[ii][jj]];
                            }
                        }
                    }
                    result = max(total_area, result);
                }
            }
        }
        return result;
    }
};