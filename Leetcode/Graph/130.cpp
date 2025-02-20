/*被围绕的区域*/
#include "../leetcode.h"

class Solution {
    int m, n;
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};
    public:
        void solve(vector<vector<char>>& board) {
            m = board.size(), n = board[0].size();
            for (int i = 0; i < m; i++) {
                if (board[i][0] == 'O') dfs(board, i, 0);
                if (board[i][n - 1] == 'O') dfs(board, i, n - 1);
            }
            for (int j = 0; j < n; j++) {
                if (board[0][j] == 'O') dfs(board, 0, j);
                if (board[m - 1][j] == 'O') dfs(board, m - 1, j);
            }
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (board[i][j] == 'C') {
                        board[i][j] = 'O';
                    } else {
                        board[i][j] = 'X';
                    }
                }
            }
        }

        void dfs(vector<vector<char>>& board, int x, int y){
            board[x][y] = 'C';
            for (int a = 0; a < 4; a++) {
                int nx = x + dx[a], ny = y + dy[a];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && board[nx][ny] == 'O') {
                    dfs(board, nx, ny);
                }
            }
        }
    };