/*有效的括号*/
#include "../leetcode.h"

bool isValid(string s) {
    stack<char> stk;
    unordered_map<char, char> ht;
    ht[')'] = '(';
    ht['}'] = '{';
    ht[']'] = '[';
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            stk.push(s[i]);
        } else {
            if (stk.empty()) return false;
            char k = stk.top();
            if (ht[s[i]] != k) return false;
            stk.pop();
        }
    }
    return stk.empty() ? true : false;
}