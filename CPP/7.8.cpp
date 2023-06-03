#include <iostream>

class Base {
public:
    void fn1() {
        std::cout << "Base::fn1() called" << std::endl;
    }

    void fn2() {
        std::cout << "Base::fn2() called" << std::endl;
    }
};

class Derived : private Base {
public:
    void callBaseFn1() {
        // 使用派生类的成员函数间接调用基类的fn1()
        fn1();
    }
};

int main() {
    Derived derived;
    derived.callBaseFn1();  // 通过Derived类的对象调用基类的fn1()

    return 0;
}