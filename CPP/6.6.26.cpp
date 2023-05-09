#include <vector>
#include <iostream>

const int N = 1e3;
int matrix[N][N];

void reverse(int n, int m) {
    std::vector<std::vector<int>> copy(n, std::vector<int>(m));
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++) {
            copy[i][j] = matrix[i][j];
        }
    }
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++) {
            matrix[j][i] = copy[i][j];
        }
    }
}

int main() {
    int n, m;
    std::cout << "请输入矩阵行数(n)和列数(m)." << std::endl;
    std::cin >> n >> m;
    std::cout << "请输入这个矩阵." << std::endl;
    for(int i = 0; i < n; i ++) {
        for(int j = 0; j < m; j ++) {
            std::cin >> matrix[i][j];
        }
    }
    reverse(n, m);
    for(int i = 0; i < m; i ++) {
        for(int j = 0; j < n; j ++) {
            std::cout << matrix[i][j] << " \n"[j == n - 1]; 
        }
    }
    return 0;
}
/**
 * Test Case:
 * Input: 
 * 2 4
 * 1 2 3 4
 * 5 6 7 8
 * Output:
 * 1 5
 * 2 6
 * 3 7
 * 4 8
 * Accurate:
 * 1 5
 * 2 6
 * 3 7
 * 4 8
 */