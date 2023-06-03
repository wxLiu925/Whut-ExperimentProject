#include <iostream>

class Point {
private:
    int x;
    int y;

public:
    Point(int xVal = 0, int yVal = 0) : x(xVal), y(yVal) {}

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    // 友元函数重载加法运算符
    friend Point operator+(const Point& p1, const Point& p2);
};

// 友元函数实现重载加法运算符
Point operator+(const Point& p1, const Point& p2) {
    int newX = p1.x + p2.x;
    int newY = p1.y + p2.y;
    return Point(newX, newY);
}

int main() {
    Point p1(2, 3);
    Point p2(4, 5);

    Point p3 = p1 + p2;

    std::cout << "p1: (" << p1.getX() << ", " << p1.getY() << ")" << std::endl;
    std::cout << "p2: (" << p2.getX() << ", " << p2.getY() << ")" << std::endl;
    std::cout << "p3: (" << p3.getX() << ", " << p3.getY() << ")" << std::endl;

    return 0;
}
