/*旋转图像*/
#include "../leetcode.h"

void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            swap(matrix[i][j], matrix[n - 1 - j][n - 1 - i]);
        }
    }
    for (int i = 0; i < n / 2; i++) {
        swap(matrix[i], matrix[n - i - 1]);
    }
}

void printVec(vector<vector<int>> matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            cout << matrix[i][j] << ' ';
        }
        cout <<endl;
    }
}

int main() {
    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    printVec(matrix);
    rotate(matrix);
    printVec(matrix);
    return 0;
}

/*
采用swap函数，对二维数组进行原地交换。
对原始矩阵的副对角线进行转置，再进行行交换即可换成rotate。
*/