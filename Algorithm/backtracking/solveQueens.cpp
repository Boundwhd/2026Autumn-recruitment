#include <vector>
#include <string>
using namespace std;


class Solution {
private:
    vector<vector<string>> result;
    void backtracking(int n, int row, vector<string> &chessboard) {
        if (row == n) {
            result.push_back(chessboard);
            return;
        }
        for (int i = 0; i < n; i++) {
            if (isValid(row, i, chessboard, n)) {
                chessboard[row][i] = 'Q';
                backtracking(n, row + 1, chessboard);
                chessboard[row][i] = '.';
            }
        }
    }
    bool isValid(int row, int col, vector<string> &chessboard, int n) {
        for (int i = 0; i < row; i++) {
            if (chessboard[i][col] == 'Q') {
                return false;
            }
        }

        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (chessboard[i][j] == 'Q') {
                return false;
            }
        }

        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (chessboard[i][j] == 'Q') {
                return false;
            }
        }
        return true;
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        result.clear();
        vector<string> chessboard(n, string(n, '.'));
        backtracking(n, 0, chessboard);
        return result;
    }
};