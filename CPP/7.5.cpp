#include <iostream>
#include <string>


class Document {
public:
    std::string name;
    Document(std::string _name): name(_name) {}
    Document() {
        name = "";
    }
};

class Book : public Document {
public:
    int pageCount;
    Book() {
        pageCount = 0;
    }
};

int main() {

    return 0;
}
