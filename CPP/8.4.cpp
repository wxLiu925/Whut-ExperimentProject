#include <iostream>

class Counter {
private:
    int count;

public:
    Counter() : count(0) {}

    int getCount() const {
        return count;
    }

    Counter operator+(int value) {
        Counter result;
        result.count = count + value;
        return result;
    }
};

int main() {
    Counter counter;
    std::cout << "一共有: " << counter.getCount() << std::endl;  // 输出初始值为 0

    counter = counter + 5;
    std::cout << "增加 5 后: " << counter.getCount() << std::endl;  // 输出增加后的值为 5

    return 0;
}