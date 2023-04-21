#include <vector>
#include <iomanip>
#include <iostream>
/**
 * @brief 实现 Newton 插值
 *
 * @param n        : 插值点的个数
 * @param x        : 需要插值计算的 x 坐标
 * @param Node_X   : 原始点横坐标, 使用 vector 存储
 * @param Node_Y   : 原始点纵坐标, 使用 vector 存储
 * @param df_Table : 商差表, n 行 n + 1 列, 使用二维 vector 存储
 *
 * @return 返回一个 double , 插值计算后得到的值
 *
 * 时间复杂度是 O(n^2)
 *
 */
double Newton(const std::vector<double>& Node_X, const std::vector<double>& Node_Y, int n, double x) {
    
    // 商插表 n 行 n + 1 列
    std::vector<std::vector<double>> df_Table(n, std::vector<double>(n + 1));

    for(int i = 0; i < n; i ++) {
        df_Table[i][0] = Node_X[i];  // 第0列为 x
        df_Table[i][1] = Node_Y[i];  // 第1列为 f(x)
    }

    /* 生成商差表 */
    for(int i = 1; i < n; i ++) {
        for(int j = 2; j < i + 2; j ++) {
            df_Table[i][j] = (df_Table[i][j - 1] - df_Table[i - 1][j - 1]) / (df_Table[i][0] - df_Table[i - j + 1][0]);
        }
    }

    /* 计算答案 */
    double y = 0.0, tmp = 1.0;
    for(int i = 0; i < n; i ++) {
        y += tmp * df_Table[i][i + 1];
        tmp *= (x - Node_X[i]);
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
        std::cout << "输入第" << i << "组数据 Node_X, Node_Y: ";
        std::cin >> Node_X[i] >> Node_Y[i]; 
    }

    std::cout << "f(" << x << ") 的近似值是 " << Newton(Node_X, Node_Y, n, x) << std::endl;
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