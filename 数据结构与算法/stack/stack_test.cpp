#include "Stack.h"
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// 实现简单计算器
class Solution {
    LinkStack<int> num;
    LinkStack<char> op;
    unordered_map<char, int> mp {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'%', 2}, {'^', 3}};
public:
    void cal() {
        if((int)num.size() < 2 || op.empty()) return;
        int x1 = num.top(); num.pop();
        int x2 = num.top(); num.pop();
        char p = op.top(); op.pop();
        int x = 0;
        if(p == '+') x = x2 + x1;
        else if(p == '-') x = x2 - x1;
        else if(p == '*') x = x2 * x1;
        else if(p == '/') x = x2 / x1;
        else if(p == '%') x = x2 % x1;
        else if(p == '^') x = x2 ^ x1;
        num.push(x);
    }
    int calculate(string s) {
        num.push(int(0));
        int n = s.size();
        for(int i = 0; i < n; i ++) {
            if(isdigit(s[i])) {
                long long x = 0;
                int j = i;
                while(j < n && isdigit(s[j])) {
                    x = x * 10 + s[j] - '0';
                    j ++;
                }
                num.push(x), i = j - 1;
            } else if(s[i] == '(')
                op.push(s[i]);
              else if(s[i] == ')') {
                  while(!op.empty()) {
                    if(op.top() != '(') cal();
                    else {
                        op.pop();
                        break;
                    }
                  }
              } else {
                  if (i > 0 && (s[i - 1] == '(' || s[i - 1] == '+' || s[i - 1] == '-'))
                    num.push(0);
                  while(!op.empty() && op.top() != '(') {
                    if(mp[op.top()] >= mp[s[i]]) cal();
                    else break;
                  }
                  op.push(s[i]);
              }
        }
        while(!op.empty() && op.top() != '(') cal();
        return num.top();
    }
};

int main() {
    // 输入表达式, -1退出
    string s; 
    while(cin >> s && s != "-1") {
        Solution sol;
        int res = sol.calculate(s);
        cout << res << endl;
    }

    return 0;
}