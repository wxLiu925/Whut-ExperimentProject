#include <vector>
#include <iomanip>
#include <iostream>
/**
 * @brief 实现拟合
 *
 * @param m       : 输入数据量
 * @param Node_X  : 原始点横坐标, 使用 vector 存储
 * @param Node_Y  : 原始点纵坐标, 使用 vector 存储
 *
 * @return 返回一个 {a, b} , 拟合的一次多项式
 *
 * 时间复杂度是 O(n^2)
 *
 */
// a + bx
struct node {
    double a, b;
};

node FIT(const std::vector<double>& Node_X, const std::vector<double>& Node_Y, int m) {
    double sx = 0.0, sy = 0.0;
    for(int i = 0; i < (int)Node_X.size(); i ++) {
        sx += Node_X[i];
    }
    for(int i = 0; i < (int)Node_Y.size(); i ++) {
        sy += Node_Y[i];
    }
    double Sx = 0.0, Sy = 0.0;
    for(int i = 0; i < (int)Node_X.size(); i ++) {
        Sx += Node_X[i] * Node_X[i];
    }
    for(int i = 0; i < (int)Node_X.size(); i ++) {
        Sy += Node_X[i] * Node_Y[i];
    }
    /*
    a * m  + b * sx  = sy
    a * sx + b * Sx = Sy
    a * sx + b * sx * (sx / m) = sy * (sx / m)
    b * (sx * (sx / m) - Sx) = sy * (sx / m) - Sy
    */
    node res;
    res.b = (sy * (sx / m) - Sy) / (sx * (sx / m) - Sx);
    res.a = (sy - res.b * sx) / m;
    return res;
}

int main() {

    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(4); // 结果保留8位小数

    std::cout << "请输入数据量 m : ";
    int m;
    std::cin >> m;
    std::vector<double> Node_X(m), Node_Y(m);
    for(int i = 0; i < m; i ++) {
        std::cout << "输入 x[" << i << "], " << "y[" << i << "]: ";
        std::cin >> Node_X[i] >> Node_Y[i]; 
    }
    auto res = FIT(Node_X, Node_Y, m);
    std::cout << "拟合结果为: P(x) = " << res.a << " + " << res.b << "x" << std::endl; 
    return 0; 
}
/**
 * Test Case:
 * Input:
 * 5
 * 165 187
 * 123 126
 * 150 172
 * 123 125
 * 141 148
 * Output:
 * P(x) = -60.9392 + 1.5138 x
 */