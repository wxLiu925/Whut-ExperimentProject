    #include <iostream>

    class Point {
    private:
        int x;
        int y;

    public:
        Point(int xVal = 0, int yVal = 0) : x(xVal), y(yVal) {}

        Point operator++() {
            ++x;
            ++y;
            return *this;
        }

        Point operator++(int) {
            Point temp(*this);
            ++(*this);
            return temp;
        }

        Point operator--() {
            --x;
            --y;
            return *this;
        }

        Point operator--(int) {
            Point temp(*this);
            --(*this);
            return temp;
        }

        void display() const {   std::cout << "Point (" << x << ", " << y << ")" << std::endl;
        }
    };

    int main() {
        Point p(3, 4);
        std::cout << "Original Point: ";
        p.display();

        Point q = ++ p;
        std::cout << "After Prefix Increment: ";
        q.display();

        Point r = p ++;
        std::cout << "After Postfix Increment: ";
        r.display();

        Point s = -- p;
        std::cout << "After Prefix Decrement: ";
        s.display();

        Point t = p --;
        std::cout << "After Postfix Decrement: ";
        t.display();

        return 0;
    }
