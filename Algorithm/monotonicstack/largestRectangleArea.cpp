#include <vector>
#include <stack>
using namespace std;
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> stk;
        if (heights.size() == 1) return heights[0];
        heights.push_back(0);
        heights.insert(heights.begin(), 0);
        stk.push(0);
        int result = 0;
        for (int i = 1; i < heights.size(); i++) {
            while (heights[i] < heights[stk.top()]) {
                int mid = stk.top();
                stk.pop();
                int w = i - stk.top() - 1;
                int h = heights[mid];
                result = max(result, w * h);
            }
            stk.push(i);
        }
        return result;
    }
};