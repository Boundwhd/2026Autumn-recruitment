#include <vector>
#include <string>
using namespace std;

class Solution {
    public:
        string removeDuplicates(string s) {
            vector<char> stk; // 使用 vector 模拟栈
            for (char ch : s) {
                if (!stk.empty() && ch == stk.back()) {
                    stk.pop_back(); // 如果当前字符与栈顶字符相同，弹出栈顶字符
                } else {
                    stk.push_back(ch); // 否则压入当前字符
                }
            }
            return string(stk.begin(), stk.end()); // 将 vector 转换为字符串
        }
    };