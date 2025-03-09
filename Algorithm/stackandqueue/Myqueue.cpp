#include <stack>
using namespace std;

class MyQueue {
private:
    stack<int> stk_in;
    stack<int> stk_out;
public:
    MyQueue() {}

    void push(int x) {
        stk_in.push(x);
    }

    int pop() {
        if (stk_out.empty()) {
            while (!stk_in.empty()) {
                int val = stk_in.top();
                stk_in.pop();
                stk_out.push(val);
            }
            int val = stk_out.top();
            stk_out.pop();
            return val;
        } 
        int val = stk_out.top();
        stk_out.pop();
        return val;
    }

    int peek() {
        if (stk_out.empty()) {
            while (!stk_in.empty()) {
                int val = stk_in.top();
                stk_in.pop();
                stk_out.push(val);
            }
            return stk_out.top();
        }
        return stk_out.top();
    }

    bool empty() {
        return (stk_in.empty() && stk_out.empty());
    }
};