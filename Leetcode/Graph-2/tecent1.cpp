#include <vector>
#include <queue>
#include <iostream>
using namespace std;

int main() {
    cout << "Give the size of grid: ";
    int n = 0;
    cin >> n;
    vector<vector<int>> board(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }

    if (board[0][0] == 1) {
        cout << -1 << endl;
        return 0;
    } else if (n == 1) {
        cout << 0 << endl;
        return 0;
    } else {
        int dx[4] = {1, 0, -1, 0};
        int dy[4] = {0, -1, 0, 1};
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        queue<pair<pair<int, int>, int>> que;
        que.push({{0, 0}, 0});
        visited[0][0] = true;
        while (!que.empty()) {
            pair<int, int> cur_pos = que.front().first;
            int cur_step = que.front().second;
            que.pop();
            for (int i = 0; i < 4; i++) {
                int x_new = cur_pos.first + dx[i];
                int y_new = cur_pos.second + dy[i];
                if (x_new >= 0 && y_new >= 0 && x_new < n && y_new < n) {
                    if (x_new == n - 1 && y_new == n - 1) {
                        cout << cur_step + 1 << endl;
                        return 0;
                    }
                    if (board[x_new][y_new] == 0 && visited[x_new][y_new] == false) {
                        visited[x_new][y_new] = true;
                        que.push({{x_new, y_new}, cur_step + 1});
                    }
                }
            }
        }
        cout << -1 << endl;
        return 0;
    }
    return 0;
}