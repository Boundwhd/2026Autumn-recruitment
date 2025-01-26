/*生命游戏*/
#include "../leetcode.h"

void gameOfLife(vector<vector<int>>& board) {
    int m = board.size();
    int n = board[0].size();

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n;j ++) {
            int sum_one = 0;
            int sum_zero = 0;
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if (x == 0 && y == 0) {
                        continue;
                    }
                    if (i + x >= 0 && i + x < m && j + y >= 0 && j + y < n) {
                        if (abs(board[i + x][j + y]) == 1) {
                            sum_one++;
                        } else {
                            sum_zero++;
                        }
                    }
                }
            }
            if (abs(board[i][j] == 1) && (sum_one < 2 || sum_one > 3)){
                board[i][j] = -1;
            } else if (abs(board[i][j] != 1) && sum_one == 3){
                board[i][j] = 2;
            }
        }
    }

    for (int i = 0;i < m; i++) {
        for (int j = 0; j < n;j ++) {
            if (board[i][j] == -1) board[i][j] = 0;
            else if (board[i][j] == 2) board[i][j] = 1;
        }
    }
}