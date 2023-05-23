#include <cmath>
#include <vector>
#include <iomanip>
#include <iostream>
/**
 * @brief 实现自适应辛普森积分
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

double simpson(double l, double r) {
    double mid = (l + r) / 2;
    return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6;  // 辛普森公式
}
double asr(double l, double r, double eps, double ans, int step) {
    double mid = (l + r) / 2;
    double fl = simpson(l, mid), fr = simpson(mid, r);
    if (abs(fl + fr - ans) <= 15 * eps && step < 0)
        return fl + fr + (fl + fr - ans) / 15;  // 足够相似的话就直接返回
    return asr(l, mid, eps / 2, fl, step - 1) + 
           asr(mid, r, eps / 2, fr, step - 1);  // 否则分割成两段递归求解
}
double calc(double l, double r, double eps) {
    return asr(l, r, eps, simpson(l, r), 12);
}


int main() {

    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(8); // 结果保留8位小数

    std::cout << "请输入积分下限和积分上限: ";
    double a, b;
    std::cin >> a >> b;

    std::cout << "积分结果为: " << calc(a, b, 1e-8) << std::endl;
    return 0;
}
/**
 * Test Case:
 * Input:
 * 0 1
 * Output:
 * 1.71828183
 * Accurate:
 * 1.71828182
 */