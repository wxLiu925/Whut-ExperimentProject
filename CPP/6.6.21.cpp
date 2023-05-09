#include <cctype>
#include <string>
#include <iostream>

int CalAlphaCnt(std::string s) {
    int res = 0;
    for(auto c: s) {
        if(isalpha(c)) res ++;
    }
    return res;
}

int main() {
    std::string s;
    getline(std::cin, s);
    std::cout << "这句话中共有 " << CalAlphaCnt(s) << " 个字母" << std::endl;
    return 0;
}
/**
 * Test Case:
 * Input: 
 * Hello, I am 10 years old.
 * Output:
 * 这句话中共有 16 个字母
 * Accurate:
 * 这句话中共有 16 个字母
 */