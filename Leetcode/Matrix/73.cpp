/*矩阵置零*/
#include "../leetcode.h"

void setZeroes(vector<vector<int>>& matrix) {
    set<int> zero_row;
    set<int> zero_col;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] == 0) {
                zero_row.insert(i);
                zero_col.insert(j);
            }
        }
    }
    for (auto elem : zero_row) {
        for (int i = 0; i < matrix[0].size(); i++) {
            matrix[elem][i] = 0;
        }
    }   

    for (auto elem : zero_col) {
        for (int j = 0; j < matrix.size(); j++) {
            matrix[j][elem] = 0;
        }
    }
}