#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        if (s.empty()) return 0;
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int result = 0;

        int i = g.size() - 1;
        int j = s.size() - 1;
        while ((j>=0) && (i>=0)) {
            if (s[j] >= g[i]) {
                j--;
                i--;
                result++;
            } else {
                i--;
            }
        }
        return result;
    }
};