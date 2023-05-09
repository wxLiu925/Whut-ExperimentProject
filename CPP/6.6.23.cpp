#include <iostream>

int main() {
    std::cout << "请输入学生总数: ";
    int n;
    std::cin >> n;
    std::cout << "下面请输入每一位学生的成绩." << std::endl;
    int sum = 0;
    for(int i = 0; i < n; i ++) {
        std::cout << "请输入第 " << i + 1 << "位学生的成绩: ";
        int x;
        std::cin >> x;
        sum += x;
    }
    std::cout << "平均成绩为: " << 1.0 * sum / n << std::endl;
    return 0;
}
/**
 * Test Case:
 * Input: 
 * 5
 * 60 70 80 90 100
 * Output:
 * 平均成绩为: 80
 * Accurate:
 * 平均成绩为: 80
 */