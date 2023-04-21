#include <vector>
#include <iomanip>
#include <iostream>
/**
 * @brief 实现 Lagrange 插值
 *
 * @param n       : 插值点的个数
 * @param x       : 需要插值计算的 x 坐标
 * @param Node_X  : 原始点横坐标, 使用 vector 存储
 * @param Node_Y  : 原始点纵坐标, 使用 vector 存储
 *
 * @return 返回一个 double , 插值计算后得到的值
 *
 * 时间复杂度是 O(n^2)
 *
 */
double Lagrange(const std::vector<double>& Node_X, const std::vector<double>& Node_Y, int n, double x) {
    double y = 0.0; // 答案
    for(int i = 0; i < n; i ++) {
        double t = 1.0; // 插值基函数 l(x)
        for(int j = 0; j < n; j ++) {
            if(i == j) continue;
            if(Node_X[i] == Node_X[j]) {
                std::cerr << "数据横坐标输入错误, 横坐标相同" << std::endl;
                exit(0);
            }
            t *= (x - Node_X[j]) / (Node_X[i] - Node_X[j]);
        }
        y += t * Node_Y[i];
    }
    return y;
}

int main() {

    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(8); // 结果保留8位小数

    std::cout << "请输入插值点 x : ";
    double x;
    std::cin >> x;

    std::cout << "请输入插值节点数目 n : ";
    int n;
    std::cin >> n;
    if(n <= 0) {
        std::cout << "输入错误\n";
        return 0;
    }
    std::vector<double> Node_X(n), Node_Y(n);
    for(int i = 0; i < n; i ++) {
        std::cout << "输入第" << i << "组数据 node_X, node_Y: ";
        std::cin >> Node_X[i] >> Node_Y[i]; 
    }

    std::cout << "f(" << x << ") 的近似值是 " << Lagrange(Node_X, Node_Y, n, x) << std::endl;
    return 0; 
}
/**
 * Test Case:
 * Input:
 * 115
 * 3
 * 100 10
 * 121 11
 * 144 12
 * Output:
 * 10.72275551
 * Accurate:
 * 10.72380529
 */