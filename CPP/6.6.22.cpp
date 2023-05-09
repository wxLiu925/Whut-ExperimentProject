#include <string>
#include <iostream>

void reverse(std::string &s) {
    static std::string s2;
    if(s.length() == s2.length()) {
        s = s2;
        return;
    }
    s2 += s.at(s.length() - s2.length() - 1);
    reverse(s);
}

int main() {
    std::string s;
    getline(std::cin, s);
    reverse(s);
    std::cout << s << std::endl;
    return 0;
}
/**
 * Test Case:
 * Input: 
 * How are you?
 * Output:
 * ?uoy era woH
 * Accurate:
 * ?uoy era woH
 */