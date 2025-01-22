/*有效的数独*/
#include "../leetcode.h"

bool isValidSudoku(vector<vector<char>>& board) {
    bool ex[9];
    for (int i = 0; i < 9; i++) {
        memset(ex, 0, sizeof(ex));
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.') continue;
            int t = board[i][j] - '1';
            if (ex[t]) return false;
            ex[t] = true;
        }
    }

    for (int i = 0; i < 9; i++) {
        memset(ex, 0, sizeof(ex));
        for (int j = 0; j < 9; j++) {
            if (board[j][i] == '.') continue;
            int t = board[j][i] - '1';
            if (ex[t]) return false;
            ex[t] = true;
        }
    }

    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3){
            memset(ex, 0, sizeof(ex));
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    if (board[i + x][j + y] == '.') continue;
                    int t = board[i + x][j + y] - '1';
                    if (ex[t]) return false;
                    ex[t] = true;
                }
            }
        }
    }
    return true;
}