#include <iostream>
class BaseClass {
public:
    virtual void fn1() {
        std::cout << "BaseClass fn1()" << std::endl;
    }
    void fn2() {
        std::cout << "BaseClass fn2()" << std::endl;
    }
};
class DerivedClass : public BaseClass {
public:
    void fn1() override {
        std::cout << "DerivedClass fn1()" << std::endl;
    }
    void fn2() {
        std::cout << "DerivedClass fn2()" << std::endl;
    }
};
int main() {
    DerivedClass derivedObj;
    BaseClass* basePtr = &derivedObj;
    basePtr->fn1();  // 通过 BaseClass 指针调用 fn1()
    basePtr->fn2();  // 通过 BaseClass 指针调用 fn2()
    DerivedClass* derivedPtr = &derivedObj;
    derivedPtr->fn1();  // 通过 DerivedClass 指针调用 fn1()
    derivedPtr->fn2();  // 通过 DerivedClass 指针调用 fn2()
    return 0;
}
