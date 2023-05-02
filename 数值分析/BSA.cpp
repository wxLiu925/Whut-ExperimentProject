#include <cmath>
#include <vector>
#include <iomanip>
#include <iostream>

template<typename A, typename B> std::ostream& operator<<(std::ostream &os, const std::pair<A, B> &p) {
    return os << '(' << p.first << ", " << p.second << ')';
}
template<typename T_container, typename T = 
typename std::enable_if<!std::is_same<T_container, std::string>::value, typename T_container::value_type>::type> 
std::ostream& operator<<(std::ostream &os, const T_container &v) { 
    os << '{'; std::string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}';
}
void debug_out() { std::cerr << std::endl; }
template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) { std::cerr << ' ' << H; debug_out(T...); }
#define debug(...) std::cerr << "(" << #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)


/**
 * @brief 自适应辛普森积分求积分
 *
 * @param l  : 积分区间左端点
 * @param r  : 积分区间右断点
 * @param f  : 被积函数
 * @return 返回一个 double , 数值积分值
 *
 */
// x^p \sqrt(1+x^2) 的积分
double f(double x, int p) {
    return pow(x, p) * sqrt(1 + (x * x));
}
double simpson(double l, double r, int p) {
    double mid = (l + r) / 2;
    return (r - l) * (f(l, p) + 4 * f(mid, p) + f(r, p)) / 6;  // 辛普森公式
}
double asr(double l, double r, double eps, double ans, int step, int p) {
    double mid = (l + r) / 2;
    double fl = simpson(l, mid, p), fr = simpson(mid, r, p);
    if (abs(fl + fr - ans) <= 15 * eps && step < 0)
        return fl + fr + (fl + fr - ans) / 15;  // 足够相似的话就直接返回
    return asr(l, mid, eps / 2, fl, step - 1, p) + 
           asr(mid, r, eps / 2, fr, step - 1, p);  // 否则分割成两段递归求解
}
double calIntegral(double l, double r, double eps, int p) {
    return asr(l, r, eps, simpson(l, r, p), 12, p);
}
/**
 * @brief 列主元消去法求解线性方程组
 *
 * @param   matrix : 增广矩阵
 * @param   n      : 增广矩阵行数
 * @param   m      : 增广矩阵列数
 * @return  0 表示唯一解, 1 表示无穷多解, 2 表示无解
 *
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

/**
 * @brief 直接求解法求最佳平方逼近式
 *
 * @param   n      : 求 n 次最佳平方逼近式
 * @return  返回一个 vector 表示结果 d{}
 *
 */
std::vector<double> BSA(int n) {
    // 先计算 d 向量
    std::vector<double> d(n + 1);
    for(int i = 0; i <= n; i ++) {
        d[i] = calIntegral(0, 1, 1e-8, i);
    }
    //debug(d);
    // 计算希尔伯特矩阵
    std::vector<std::vector<double>> H(n + 1, std::vector<double>(n + 2));
    for(int i = 0; i <= n; i ++) {
        for(int j = 0; j <= n; j ++) {
            H[i][j] = 1.0 / (i + j + 1);
        }
    }
    //debug(H);
    // 希尔伯特矩阵H -> 增广矩阵
    for(int i = 0; i < n + 1; i ++) {
        H[i][n + 1] = d[i];
    }
    std::vector<double> a; // 答案
    gauss(H, n + 1, n + 2, a); // 一定有解
    return a;
}

int main() {
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "请输入最佳平方逼近式次数: ";
    int n;
    std::cin >> n;
    auto res = BSA(n);
    std::cout << "该逼近多项式的次数依次是:\n";
    for(auto t: res) std::cout << t << " ";
    std::cout << std::endl;
    return 0;
}

/**
 * Test Case:
 * Input:
 * 1
 * Output:
 * 0.934 0.427
 * Accurate:
 * 0.934 0.427
 */