#include <iostream>

using namespace std;

template<typename T>
class unique_ptr {
private:
    T* ptr;

public:
    explicit unique_ptr(T* p = nullptr) : ptr(p) {}

    unique_ptr(const unique_ptr& other) = delete;

    unique_ptr& operator=(const unique_ptr& other) = delete;

    unique_ptr(unique_ptr&& other) noexcept : ptr (other.ptr) {
        other.ptr = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this != &other) {
            delete this->ptr;
            this->ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T* get_ptr() {
        return static_cast<T*>(ptr);
    }

    ~unique_ptr() {
        delete ptr;
    }
};

int main() {
    unique_ptr<int> ptr1(new int(5));
    cout << "ptr1->" << *ptr1.get_ptr() << endl;

    unique_ptr<int> ptr2 = move(ptr1);
    cout << "ptr2->" << *ptr2.get_ptr() << endl;
    if (ptr1.get_ptr() == nullptr) {
        cout << "ptr1 = null" << endl;
    } else {
        cout << "ptr2 != null" << endl;
    }

    ptr1 = move(ptr2);
    cout << "ptr1->" << *ptr1.get_ptr() << endl;
    if (ptr2.get_ptr() == nullptr) {
        cout << "ptr2 = null" << endl;
    } else {
        cout << "ptr2 != null" << endl;
    }

    return 0;
}