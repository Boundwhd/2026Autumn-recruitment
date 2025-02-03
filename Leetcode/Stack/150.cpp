/*逆波兰表达式求值*/
#include "../leetcode.h"

int evalRPN(vector<string>& tokens) {
    stack<int> stk;
    int ans = 0;
    for (int i = 0; i < tokens.size(); i++) {
        string word = tokens[i];
        if (word == "+" || word == "-" || word == "*" || word == "/") {
            int a = stk.top();
            stk.pop();
            int b = stk.top();
            stk.pop();
            if (word == "+") stk.push(b + a);
            else if (word == "-") stk.push(b - a);
            else if (word == "*") stk.push(b * a);
            else stk.push(b / a);
        } else {
            stk.push(stoi(word));
        }
    }
    return stk.top();
}

int main() {
    vector<string> tokens = {"-11", "2", "+", "5"};
    int a =  stoi(tokens[0]);
    cout << a << endl;
    return 0;
}

/*stoi用于将字符串转换为整数*/