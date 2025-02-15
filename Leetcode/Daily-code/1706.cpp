/*球会落何处*/
#include "../leetcode.h"

vector<int> findBall(vector<vector<int>>& grid) {
    int row = grid.size();
    int col = grid[0].size();
    vector<int> result(col, -1);

    for (int i = 0; i < col; i++) {
        int cur_col = i;
        bool break_flag = false;
        for (int j = 0; j < row; j++) {
            if (grid[j][cur_col] == 1) {
                if (cur_col + 1 < col && grid[j][cur_col+1] == 1) {
                    cur_col += 1;
                } else {
                    break_flag = true;
                    break;
                }
            } else {
                if (cur_col - 1 >= 0 && grid[j][cur_col-1] == -1) {
                    cur_col -= 1;
                } else {
                    break_flag = true;
                    break;
                }
            }
        }
        if (!break_flag) result[i] = cur_col;
    }

    return result;
}

int main() {
    vector<int> a(2, -1);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++){
            cout << "no break0" << endl;
            if (j == 0) break;
            if (j == 1) break;
            cout << "no break1" << endl;
        }
    } 
    return 0;
}