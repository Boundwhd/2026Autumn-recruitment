#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    static bool cmp(vector<int> a, vector<int> b) {
        return a[0] < b[0];
    }
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.size() == 1) return 1;
        sort(points.begin(), points.end(), cmp);
        int arrow = 1;
        for (int i = 1; i < points.size(); i++) {
            if (points[i][0] > points[i - 1][1]) {
                arrow++;
            } else {
                points[i][1] = min(points[i - 1][1], points[i][1]);
            }
        }
        return arrow;
    }
};