#include <cmath>
#include <vector>
#include <iomanip>
#include <iostream>

// y' = y - 2x/y , x\in [0, 1]
double f(double x, double y) {
    return (y - 2.0 * x / y);
}

/**
 * @brief 改进的欧拉法(二阶方法)
 *
 * @param   x0  : 起点
 * @param   y0  : 起点
 * @param   h   : 步长
 * @param   n   : 划分数
 * @param   res : 结果
 *
 */
void Runge_Kutta(double x0, double y0, double h, int n, std::vector<double> &res) {
    double K1 = 0.0, K2 = 0.0, K3 = 0.0, K4 = 0.0;
    for(int i = 1; i <= n; i ++) {
        K1 = f(x0, y0);
        K2 = f(x0 + h / 2, y0 + h / 2 * K1);
		K3 = f(x0 + h / 2, y0 + h / 2 * K2);
		K4 = f(x0 + h, y0 + h * K3);
        y0 += h / 6 * (K1 + 2.0 * K2 + 2.0 * K3 + K4);
        std::cout << "n = " << i << "时：\t" << "yn = " << y0 << std::endl;
        res.push_back(y0);
        x0 += h;
    }
}

int main() {

    std::vector<double> res;
    Runge_Kutta(0, 1, 0.1, 10, res);

    std::cout << "误差分析(2范)" << std::endl;
    std::vector<double> accurate = {1.095445, 1.183216, 1.264991, 1.341641, 1.414214, 1.483240, 1.549193, 1.612452, 1.673320, 1.763051};
    double eps = 0.0;
    for(int i = 0; i < (int)res.size(); i ++) {
        eps += (res[i] - accurate[i]) * (res[i] - accurate[i]);
    }
    eps = sqrt(eps);
    std::cout << std::fixed << std::setprecision(12) << eps << std::endl;
    return 0;
}