#include <stack>
#include <string>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        if (s.size() % 2 != 0) return false;
        stack<char> stk;
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
                stk.push(s[i]);
            } else {
                if (stk.empty()) return false;
                char k = stk.top();
                stk.pop();
                if (s[i] == ')' && k == '(') continue;
                else if (s[i] == ']' && k == '[') continue;
                else if (s[i] == '}' && k == '{') continue;
                else return false;
            }
        }
        return stk.empty();
    }
};