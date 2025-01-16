#include <iostream>
using namespace std;

class MyClass {
private:
    // 静态成员变量
    static int staticVar;

public:
    // 构造函数
    MyClass() {
        // 每次创建对象时打印一个消息
        cout << "Object created!" << endl;
    }

    // 静态成员函数
    static void incrementStaticVar() {
        staticVar++;  // 增加静态成员变量的值
    }

    // 静态成员函数，返回静态变量
    static int getStaticVar() {
        return staticVar;
    }
};

// 定义静态成员变量
int MyClass::staticVar = 0;

int main() {
    // 通过类名直接访问静态成员函数
    MyClass::incrementStaticVar();  // 静态函数通过类名访问
    MyClass::incrementStaticVar();
    MyClass::incrementStaticVar();

    // 通过类名访问静态成员变量
    cout << "Static Variable Value: " << MyClass::getStaticVar() << endl;

    // 创建对象，通过对象访问静态成员
    MyClass obj1;
    obj1.incrementStaticVar();
    cout << "Static Variable Value (after object increment): " << MyClass::getStaticVar() << endl;

    return 0;
}
