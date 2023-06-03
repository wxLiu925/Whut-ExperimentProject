#include <iostream>

class BaseClass {
public:
    void fn1() {
        std::cout << "BaseClass::fn1() called" << std::endl;
    }

    void fn2() {
        std::cout << "BaseClass::fn2() called" << std::endl;
    }
};

class DerivedClass : public BaseClass {
public:
    void fn1() {
        std::cout << "DerivedClass::fn1() called" << std::endl;
    }

    void fn2() {
        std::cout << "DerivedClass::fn2() called" << std::endl;
    }
};

int main() {
    DerivedClass derivedObj;

    // 使用BaseClass指针调用成员函数
    BaseClass* basePtr = &derivedObj;
    basePtr->fn1();
    basePtr->fn2();

    // 使用DerivedClass指针调用成员函数
    DerivedClass* derivedPtr = &derivedObj;
    derivedPtr->fn1();
    derivedPtr->fn2();

    return 0;
}
