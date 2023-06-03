#include <iostream>

class BaseClass {
public:
    virtual ~BaseClass() {
        std::cout << "BaseClass destructor" << std::endl;
    }
};

class DerivedClass : public BaseClass {
public:
    ~DerivedClass() override {
        std::cout << "DerivedClass destructor" << std::endl;
    }
};

int main() {
    BaseClass* basePtr = new DerivedClass();
    delete basePtr;

    return 0;
}
