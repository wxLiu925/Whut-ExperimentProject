#include <cmath>
#include <vector>
#include <iomanip>
#include <iostream>

/**
 * @brief 列主元消去法求解线性方程组
 *
 * @param   matrix : 增广矩阵
 * @param   n      : 增广矩阵行数
 * @param   m      : 增广矩阵列数
 * @param   b      : 若有唯一解, 存储答案
 * @return  0 表示唯一解, 1 表示无穷多解, 2 表示无解
 *
 * 时间复杂度是 O(n^3)
 */
const double eps = 1e-8;
int gauss(std::vector<std::vector<double>> matrix, int n, int m, std::vector<double>& b) {
    // r 表示行号, c表示列号
    int r, c;
    for(r = 0, c = 0; c < m - 1; c ++) { 
        int t = r;
        // 找到当前列中绝对值最大的元素
        for(int i = r; i < n; i ++) {
            if(fabs(matrix[i][c]) > fabs(matrix[t][c])) {
                t = i;
            }
        }
        if(fabs(matrix[t][c]) < eps) continue; // 如果这一列全0的话，直接跳过
        for(int i = c; i < m; i ++) 
            std::swap(matrix[t][i], matrix[r][i]); // 将最大值所在的行移到最上面
        for(int i = m - 1; i >= c; i --) matrix[r][i] /= matrix[r][c]; // 将主元变成1
        for(int i = r + 1; i < n; i ++) {
            if(fabs(matrix[i][c]) > eps) {
                for(int j = m - 1; j >= c; j --) {
                    matrix[i][j] -= matrix[i][c] * matrix[r][j]; // 将下面所以行都减去当前行的a[i][c]倍
                }
            }
        }
        r ++;
    }
    if(r < n) {
        for(int i = r; i < n; i ++) {
            if(fabs(matrix[i][m - 1]) > eps) { // 若bi不为0，则无解
                return 2;
            }
        }
        return 1;
    }
    b.resize(n);
    for(int i = 0; i < n; i ++) {
        b[i] = matrix[i][m - 1];
    }
    for(int i = n - 1; i >= 0; i --) {
        for(int j = i + 1; j < n; j ++) {
            b[i] -= b[j] * matrix[i][j];
        }
    }
    return 0;
}

int main() {

    int n, m;
    std::cin >> n >> m; // 增广矩阵行数和列数

    std::vector<std::vector<double>> matrix(n, std::vector<double>(m)); // n 行 m + 1 列矩阵表示增广矩阵
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++) {
            std::cin >> matrix[i][j];
        }
    }
    std::vector<double> ans;
    int result = gauss(matrix, n, m, ans);
    if(result == 0) {
        // 求出的结果
        for(int i = 0; i < (int)ans.size(); i ++) {
            std::cout << ans[i] << " \n"[i == (int)ans.size() - 1];
        }

        // 误差分析, 取二范数
        double eps = 0.0;
        // 对于这个例子的正确答案
        std::vector<double> accurate = {-37.0 / 38, 197.0 / 38, -91.0 / 38};
        for(int i = 0; i < 3; i ++) {
            eps += (accurate[i] - ans[i]) * (accurate[i] - ans[i]);
        }
        eps = sqrt(eps);
        std::cout << "误差为(2范): " << std::fixed << std::setprecision(16) << eps << std::endl; // 输出精度 保留16位小数
    } else if(result == 1) {
        std::cout << "方程组有无穷多组解！" << std::endl;
    } else {
        std::cout << "方程组无解！" << std::endl;
    }
    return 0;
}
/**
 * Test Case:
 * Input:
 * 3 4
 * 1 3 4 5
 * 1 4 7 3
 * 9 3 2 2
 * Output:
 * -0.973684 5.18421 -2.39474
 * Accurate:
 * -37/38 197/38 -91/38
 * 
 * 输出精度为: 0.0000000000000019
 */