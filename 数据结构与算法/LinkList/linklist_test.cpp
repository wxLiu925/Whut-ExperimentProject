#include "linklist.h"
#include "linklist.cpp"
#include <iostream>

void test() {
    ElemType A[] = {1, 3, 2, 3, 4, 10, 5, 7, 8, 5, 9};
    int n = sizeof(A) / sizeof(int);

    LinkNode list; 
    list.CreateListT(A, n); //建表
    std::cout << "初始链表: ";
    list.DispList();
    std::cout << std::endl; 

    int len = list.ListLength();
    std::cout << "链表长度为: " << len << std::endl; //输出链表长度

    //删除链表第5个元素
    list.ListDelete(5);
    std::cout << "删除链表第五个元素后的链表: ";
    list.DispList();
    std::cout << std::endl; 

    //在第7个位置插入4
    list.ListInsert(7, 4);
    std::cout << "在第7个位置插入4后的链表: ";
    list.DispList();
    std::cout << std::endl; 

    //删除元素值最大的元素
    list.DelMaxNode();
    std::cout << "删除元素值最大的元素后的链表: ";
    list.DispList();
    std::cout << std::endl; 
}

int main() {
    test();
    return 0;
}