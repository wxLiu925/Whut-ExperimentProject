#include <iostream>

using namespace std;

class Mammal {
public:
    virtual void speak() {
        cout << "Mammal speaks." << endl;
    }
};

class Dog : public Mammal {
public:
    void speak() override {
        cout << "Dog barks." << endl;
    }
};

int main() {
    Dog dog;
    dog.speak();  // 通过 Dog 对象调用 speak 函数

    return 0;
}
