/*基本计算器*/
#include "../leetcode.h"

int calculate(string s) {
    stack<int> stk;
    int result = 0;
    int sign = 1;
    int num = 0;

    for (auto ch : s) {
        if (isdigit(ch)) {
            num = num * 10 + (ch - '0');
        } else if (ch == '+') {
            result += sign * num;
            num = 0;
            sign = 1;
        } else if (ch == '-') {
            result += sign * num;
            num = 0;
            sign = -1;
        } else if (ch == '(') {
            stk.push(result);
            stk.push(sign);
            result = 0;
            sign = 1;
        } else if (ch == ')') {
            result += sign * num;
            num = 0;
            result *= stk.top();
            stk.pop();
            result += stk.top();
            stk.pop();
        }
    }

    result += sign * num;
    return result;
}

int main() {
    string s = "(1+(4+5+2)-3)+(6+8)";
    int ans = calculate(s);
    cout << "计算结果: " << calculate(s) << endl;  // 输出: 23
    return 0;
}