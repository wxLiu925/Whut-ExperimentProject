#include <iostream>

class Object {
private:
    double weight;

public:
    Object(double objWeight) : weight(objWeight) {
        std::cout << "Object constructor called" << std::endl;
    }

    ~Object() {
        std::cout << "Object destructor called" << std::endl;
    }

    void setWeight(double objWeight) {
        weight = objWeight;
    }

    double getWeight() const {
        return weight;
    }
};

class Box : public Object {
private:
    double height;
    double width;

public:
    Box(double objWeight, double boxHeight, double boxWidth)
        : Object(objWeight), height(boxHeight), width(boxWidth) {
        std::cout << "Box constructor called" << std::endl;
    }

    ~Box() {
        std::cout << "Box destructor called" << std::endl;
    }

    void setDimensions(double boxHeight, double boxWidth) {
        height = boxHeight;
        width = boxWidth;
    }

    double getHeight() const {
        return height;
    }

    double getWidth() const {
        return width;
    }
};

int main() {
    Box myBox(10.0, 5.0, 3.0);
    std::cout << "Weight: " << myBox.getWeight() << std::endl;
    std::cout << "Height: " << myBox.getHeight() << std::endl;
    std::cout << "Width: " << myBox.getWidth() << std::endl;

    return 0;
}
