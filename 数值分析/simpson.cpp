#include <cmath>
#include <vector>
#include <iomanip>
#include <iostream>
/**
 * @brief 实现辛普森积分
 *
 * @param f(x)     : 被积函数
 * @param a        : 积分上限
 * @param b        : 积分下限
 *
 * @return 返回一个 double ,  $\int_a^b f(x)dx$ 的近似值
 *
 */
double f(double x) {
    return exp(x); // f(x) = e^x
}

const int N = 1000 * 1000;
double simpson_integration(double a, double b) {
    double h = (b - a) / N;
    double s = f(a) + f(b);
    for (int i = 1; i <= N - 1; ++i) {
        double x = a + h * i;
        s += f(x) * ((i & 1) ? 4 : 2);
    }
    s *= h / 3;
    return s;
}


int main() {

    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(8); // 结果保留8位小数

    std::cout << "请输入积分下限和积分上限: ";
    double a, b;
    std::cin >> a >> b;

    std::cout << "积分结果为: " << simpson_integration(a, b) << std::endl;
    return 0;
}
/**
 * Test Case:
 * Input:
 * 1 2
 * Output:
 * 1.71828183
 * Accurate:
 * 1.71828182
 */