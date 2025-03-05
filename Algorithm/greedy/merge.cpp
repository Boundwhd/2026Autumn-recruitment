#include <vector>
#include <algorithm>
using namespace std;

class Solution {
    static bool cmp(vector<int>& a, vector<int>& b) {
        return a[0] < b[0];
    }
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.size() == 1) return intervals;
        sort(intervals.begin(), intervals.end(), cmp);
        vector<vector<int>> result;
        int cur_end = intervals[0][1];
        int cur_start = intervals[0][0];
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] <= cur_end) {
                cur_end = max(intervals[i][1], cur_end);
            } else {
                result.push_back({cur_start, cur_end});
                cur_start = intervals[i][0];
                cur_end = intervals[i][1];
            }
        }
        result.push_back({cur_start, cur_end});
        return result;
    }
};