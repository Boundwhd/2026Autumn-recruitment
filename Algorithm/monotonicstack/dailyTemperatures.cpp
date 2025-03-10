#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        if (n == 1) return {0};
        stack<int> stk;
        vector<int> result(n, 0);

        stk.push(0);
        for (int i = 1; i < n; i++) {
            while (!stk.empty() && temperatures[i] > temperatures[stk.top()]) {
                result[stk.top()] = i - stk.top();
                stk.pop();
            }
            stk.push(i);
            if (temperatures[i] <= temperatures[stk.top()]) {
                stk.push(i);
            }
        }
        return result;
    }
};