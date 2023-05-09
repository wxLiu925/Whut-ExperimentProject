#include <iostream>

class SimpleCircle {
private:
    int *itsRadius;
public:
    SimpleCircle(int r) {
        itsRadius = new int(r);
    }
    ~SimpleCircle() {
        if(itsRadius != NULL) {
            itsRadius = NULL;
        }
    }
    SimpleCircle operator + (const SimpleCircle& c) const {
        if(this->itsRadius == NULL || c.itsRadius == NULL) {
            throw std::runtime_error("对空类进行加法操作!");
        }
        return SimpleCircle(*this->itsRadius + *c.itsRadius);
    }
    SimpleCircle operator - (const SimpleCircle& c) const {
        if(this->itsRadius == NULL || c.itsRadius == NULL) {
            throw std::runtime_error("对空类进行加法操作!");
        }
        return SimpleCircle(*this->itsRadius - *c.itsRadius);
    }
public:
    void display() {
        if(itsRadius == NULL) {
            std::cout << "半径值为空！" << std::endl;
        } else {
            std::cout << "半径为: " << *itsRadius << std::endl;
        }
    }
    void update(int r) {
        itsRadius = new int(r);
    }

};

void test() {
    SimpleCircle R1(2), R2(4);
    R1.display();
    R2.display();
    R1 = R1 + R2;
    R1.display();
    R1.update(1);
    R1.display();
}

int main() {
    test();
    return 0;
}