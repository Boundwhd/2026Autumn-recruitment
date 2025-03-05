#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    static bool cmp(vector<int> a, vector<int> b) {
        if (a[0] == b[0]) {
            return a[1] < b[1];
        }
        return a[0] < b[0];
    }
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.size() == 1) return 0;
        sort(intervals.begin(), intervals.end(), cmp);
        int cur_end = intervals[0][1];
        int result = 0;
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] < cur_end) {
                result++;
                cur_end = min(cur_end, intervals[i][1]);
            } else {
                cur_end = intervals[i][1];
            }
        }
        return result;
    }
};