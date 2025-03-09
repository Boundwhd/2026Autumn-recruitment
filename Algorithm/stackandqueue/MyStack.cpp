#include <queue>
using namespace std;

class MyStack{
private:
    queue<int> que1; //工作队列
    queue<int> que2; //存储队列
public:
    MyStack() {}

    void push(int x) {
        que1.push(x);
    }

    int pop() {
        int size = que1.size();
        while (size-- > 1) {
            que2.push(que1.front());
            que1.pop();
        }
        int result = que1.front();
        que1.pop();
        while(!que2.empty()) {
            que1.push(que2.front());
            que2.pop();
        }
        return result;
    }

    int top() {
        int size = que1.size();
        while (size-- > 1) {
            que2.push(que1.front());
            que1.pop();
        }
        int result = que1.front();
        que2.push(que1.front());
        que1.pop();
        while(!que2.empty()) {
            que1.push(que2.front());
            que2.pop();
        }
        return result;
    }

    bool empty() {
        return que1.empty();
    }
};