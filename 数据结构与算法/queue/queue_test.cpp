#include "Queue.h"
#include <iostream>
#include <vector>

int main() {
    int n;
    LinkQueue<int> q;
    std::vector<int> ans;
    while(std::cin >> n && n) {
        q.clear(), ans.clear();
        for(int i = 1; i <= n; i ++)
            q.enqueue(i);
        bool now = true; //true表示现在要报数, false表示不报数
        while(!q.empty()) {
            auto t = q.Front(); q.dequeue();
            if(now) ans.push_back(t); //报数
            else q.enqueue(t); //不报数, 放到队尾
            now = !now;
        }
        for(int i = 0; i < n; i ++)
            std::cout << ans[i] << " \n"[i == n - 1];
    }
    return 0;
}