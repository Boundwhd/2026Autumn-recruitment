/*用最少数量的箭引爆气球*/
/*
1. 将所有气球按照 end 升序排列
2. 贪心算法
*/
#include "../leetcode.h"

int findMinArrowShots(vector<vector<int>>& points) {
    if (points.size() == 1) return 1;

    sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1];
    });

    int arrows = 1;
    int arrowPos = points[0][1];

    for (int i = 1; i < points.size(); i++) {
        if (points[i][0] > arrowPos) {
            arrows++;
            arrowPos = points[i][1];
        }
    }

    return arrows;
}