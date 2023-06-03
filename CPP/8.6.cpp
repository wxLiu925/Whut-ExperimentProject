#include <iostream>


class Shape {
public:
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
};

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double getArea() const override {
        return width * height;
    }

    double getPerimeter() const override {
        return 2 * (width + height);
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double getArea() const override {
        return 3.14159 * radius * radius;
    }

    double getPerimeter() const override {
        return 2 * 3.14159 * radius;
    }
};

int main() {
    Rectangle rectangle(4, 5);
    std::cout << "Rectangle Area: " << rectangle.getArea() << std::endl;
    std::cout << "Rectangle Perimeter: " << rectangle.getPerimeter() << std::endl;

    Circle circle(3);
    std::cout << "Circle Area: " << circle.getArea() << std::endl;
    std::cout << "Circle Perimeter: " << circle.getPerimeter() << std::endl;

    return 0;
}
