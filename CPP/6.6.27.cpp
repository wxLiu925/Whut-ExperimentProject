#include <iostream>

class Employee {
private:
    std::string name;
    std::string street;
    std::string city;
    std::string postcode;
public:
    Employee(std::string name_t, std::string street_t, std::string city_t, std::string postcode_t) :
        name(name_t), 
        street(street_t),
        city(city_t),
        postcode(postcode_t) { }
    Employee(const Employee& c) {
        name = c.name;
        street = c.street;
        city = c.city;
        postcode = c.postcode;
    }
public:
    void setName(std::string s) {
        name = s;
    }
    void display() {
        std::cout << "-----------------------------" << std::endl;
        std::cout << "姓名: " << name      << std::endl;
        std::cout << "街道: " << street    << std::endl;
        std::cout << "城市: " << city      << std::endl;
        std::cout << "邮编: " << postcode  << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }
};

int main() {
    Employee e("张三", "洪山街道", "武汉", "114514");
    e.display();
    e.setName("李四");
    e.display();
    return 0;
}