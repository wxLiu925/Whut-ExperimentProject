#include <vector>
#include <iostream>

int matrix[3][3];

void reverse() {
    for(int i = 0; i < 3; i ++) {
        for(int j = 0; j < i; j ++) {
            std::swap(matrix[i][j], matrix[j][i]);
        }
    }
}

int main() {
    std::cout << "请输入这个3x3矩阵." << std::endl;
    for(int i = 0; i < 3; i ++) {
        for(int j = 0; j < 3; j ++) {
            std::cin >> matrix[i][j];
        }
    }
    reverse();
    for(int i = 0; i < 3; i ++) {
        for(int j = 0; j < 3; j ++) {
            std::cout << matrix[i][j] << " \n"[j == 2]; 
        }
    }
    return 0;
}
/**
 * Test Case:
 * Input: 
 * 1 2 3
 * 4 5 6
 * 7 8 9
 * Output:
 * 1 4 7
 * 2 5 8
 * 3 6 9
 * Accurate:
 * 1 4 7
 * 2 5 8
 * 3 6 9
 */