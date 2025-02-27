#include <iostream>

using namespace std;

template<typename T>
class shared_ptr {
private:
    T* ptr;
    size_t* cnt;

    void release() {
        if (cnt && --(*cnt) == 0) { // 引用计数减 1
            delete ptr;
            delete cnt;
        }
    }

public:
    explicit shared_ptr(T* p = nullptr) : ptr(p), cnt(new size_t(1)) {
        if (p == nullptr) {
            *cnt = 0;
        }
    }

    shared_ptr(const shared_ptr& other) : ptr(other.ptr),cnt(other.cnt) {
        if (ptr) {
            (*cnt)++;
        }
    }

    shared_ptr& operator=(const shared_ptr& other) {
        if (this != &other) {
            release();
            this->ptr = other.ptr;
            this->cnt = other.cnt;
            if(this->ptr != nullptr) {
                (*cnt)++;
            }
        }
        return *this;
    }

    shared_ptr& operator=(shared_ptr&& other) {
        if (this != &other) {
            release();
            this->cnt = other.cnt;
            this->ptr = other.ptr;
            other.cnt = nullptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    shared_ptr(shared_ptr&& other) noexcept : ptr(other.ptr), cnt(other.cnt) {
        if (this->ptr) {
            other.ptr = nullptr;
            other.cnt = nullptr;
        }
    }

    int get_cnt () {
        return *cnt;
    }

    T* get_ptr() {
        return static_cast<T*>(ptr);
    }

    ~shared_ptr(){
        release();
        cout << "delete" << endl;
    }
};

// 测试函数
void test_shared_ptr() {
    // 测试 1: 基本功能
    {
        shared_ptr<int> ptr1(new int(10));
        std::cout << "Test 1: Basic functionality" << std::endl;
        std::cout << "ptr1 value: " << *ptr1.get_ptr() << ", use_count: " << ptr1.get_cnt() << std::endl; // 输出: 10, 1
    } // ptr1 离开作用域，资源被释放

    // 测试 2: 拷贝构造函数
    {
        shared_ptr<int> ptr1(new int(20));
        shared_ptr<int> ptr2(ptr1); // 拷贝构造
        std::cout << "\nTest 2: Copy constructor" << std::endl;
        std::cout << "ptr1 use_count: " << ptr1.get_cnt() << std::endl; // 输出: 2
        std::cout << "ptr2 use_count: " << ptr2.get_cnt() << std::endl; // 输出: 2
    } // ptr1 和 ptr2 离开作用域，资源被释放

    // 测试 3: 拷贝赋值运算符
    {
        shared_ptr<int> ptr1(new int(30));
        shared_ptr<int> ptr2;
        ptr2 = ptr1; // 拷贝赋值
        std::cout << "\nTest 3: Copy assignment operator" << std::endl;
        std::cout << "ptr1 use_count: " << ptr1.get_cnt() << std::endl; // 输出: 2
        std::cout << "ptr2 use_count: " << ptr2.get_cnt() << std::endl; // 输出: 2
    } // ptr1 和 ptr2 离开作用域，资源被释放

    // 测试 4: 移动构造函数
    {
        shared_ptr<int> ptr1(new int(40));
        shared_ptr<int> ptr2(std::move(ptr1)); // 移动构造
        std::cout << "\nTest 4: Move constructor" << std::endl;
        std::cout << "ptr1 use_count: " << (ptr1.get_ptr() ? ptr1.get_cnt() : 0) << std::endl; // 输出: 0
        std::cout << "ptr2 use_count: " << ptr2.get_cnt() << std::endl; // 输出: 1
    } // ptr2 离开作用域，资源被释放

    // 测试 5: 移动赋值运算符
    {
        shared_ptr<int> ptr1(new int(50));
        shared_ptr<int> ptr2;
        ptr2 = std::move(ptr1); // 移动赋值
        std::cout << "\nTest 5: Move assignment operator" << std::endl;
        std::cout << "ptr1 use_count: " << (ptr1.get_ptr() ? ptr1.get_cnt() : 0) << std::endl; // 输出: 0
        std::cout << "ptr2 use_count: " << ptr2.get_cnt() << std::endl; // 输出: 1
    } // ptr2 离开作用域，资源被释放

    // 测试 6: 自我赋值
    {
        shared_ptr<int> ptr1(new int(60));
        ptr1 = ptr1; // 自我赋值
        std::cout << "\nTest 6: Self assignment" << std::endl;
        std::cout << "ptr1 use_count: " << ptr1.get_cnt() << std::endl; // 输出: 1
    } // ptr1 离开作用域，资源被释放

    // 测试 7: 析构函数
    {
        shared_ptr<int> ptr1(new int(70));
        {
            shared_ptr<int> ptr2 = ptr1; // 拷贝构造
            std::cout << "\nTest 7: Destructor" << std::endl;
            std::cout << "ptr1 use_count: " << ptr1.get_cnt() << std::endl; // 输出: 2
            std::cout << "ptr2 use_count: " << ptr2.get_cnt() << std::endl; // 输出: 2
        } // ptr2 离开作用域，引用计数减 1
        std::cout << "ptr1 use_count after ptr2 destruction: " << ptr1.get_cnt() << std::endl; // 输出: 1
    } // ptr1 离开作用域，资源被释放
}

int main() {
    test_shared_ptr();
    return 0;
}

