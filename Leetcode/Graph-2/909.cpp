/*蛇梯棋*/
#include "../leetcode.h"

class Solution {
    public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size();
        int target = n * n;

        auto getPosition = [n](int num) -> pair<int, int> {
            int row = (num - 1) / n;
            int col = (num - 1) % n;
            if (row % 2 == 1) {
                col = n - 1 - col;
            }
            return {n - 1 - row, col};
        };

        queue<pair<int, int>> q; // {当前编号，投掷次数}
        q.push({1, 0});
        unordered_set<int> visited;
        visited.insert(1);

        while(!q.empty()) {
            auto curr = q.front();
            q.pop();
            int currNum = curr.first;
            int step = curr.second;

            //遍历骰子的六种可能
            for(int i = 1; i <= 6; i++) {
                int nextNum = currNum + i;
                if (nextNum > target){
                    break;
                }
                
                auto pos = getPosition(nextNum);
                int r = pos.first, c = pos.second;

                if (board[r][c] != -1) {
                    nextNum = board[r][c];
                }

                if (nextNum == target) {
                    return step + 1;
                }

                if (visited.find(nextNum) == visited.end()) {
                    visited.insert(nextNum);
                    q.push({nextNum, step + 1});
                }
            }
        }
        return -1;
    }
};

