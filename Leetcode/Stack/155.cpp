/*最小栈*/
#include "../leetcode.h"

class MinStack {
public:
    stack<pair<int, int>> stk;
    MinStack() {
        
    }
    
    void push(int val) {
        if (stk.empty()) {
            stk.push(make_pair(val, val));
        } else {
            int last_num = stk.top().second;
            if (last_num <= val) {
                stk.push(make_pair(val, last_num));
            } else {
                stk.push(make_pair(val, val));
            }
        }
    }
    
    void pop() {
        if (!stk.empty()) {
            stk.pop();
        }
    }
    
    int top(){
        return stk.top().first;
    }
    
    int getMin() {
        return stk.top().second;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */