#include "linklist.h"
#include <iostream>
#include <algorithm>

void LinkNode::Initlist() {
    head = new Node(0); //初始化单链表L, 头节点的数据域代表链表长度, 现在为0
}

int LinkNode::ListLength() {
    return head->data; //链表长度
}

//在链表的第i个位置后面插入元素e
void LinkNode::ListInsert(int idx, ElemType e) {
    auto now = head;
    auto insert = new LinkNode::Node(e);
    int len = ListLength();
    //如果链表长度小于i, 则直接插到链表尾部
    idx = (len < idx) ? len : idx;
    idx = std::max(1, idx); // 如果idx为0即链表长度为空直接插到第一个位置
    for(int i = 0; i < idx; i ++) {
        now = now->next;
    }
    insert->next = now->next;
    now->next = insert;
    head->data ++;
}

//删除单链表L的第i个元素
void LinkNode::ListDelete(int idx) {
    if(head->data == 0) {
        std::cout << "链表为空" << std::endl;
        return; //链表为空
    } else if(head->data < idx) {
        std::cout << "链表长度不足" << idx << std::endl;
        return;
    }
    auto now = head;
    for(int i = 0; i < idx-1; i ++)
        now = now->next;
    now->next = now->next->next; //直接让要删除节点的上一个节点指向它的下一个节点, 若没有指向空
    head->data --;
}

//输出单链表L
void LinkNode::DispList() {
    int len = head->data;
    if(len == 0) {
        std::cout << "链表为空" << std::endl;
        return;
    }
    auto now = head->next;
    for(int i = 0; i < len; i ++) {
        std::cout << now->data << " ";
        now = now->next;
    }
    std::cout << std::endl;
}

//使用头插法初始化单链表, 头插法每次把头节点插入到头节点后面, 链表顺序与输入顺序相反
//头插法可以防止空链表的出现
void LinkNode::CreateListT(ElemType A[], int n) {
    for(int i = 0; i < n; i ++) {
        auto *now = new LinkNode::Node(A[i]);
        now->next = head->next;
        head->next = now;
        head->data ++;
    }
}

//删除单链表中元素值最大的结点
void LinkNode::DelMaxNode() {
    if(ListLength() == 0) {
        std::cout << "链表为空" << std::endl;
        return;
    }
    auto pre_max_Node = head; //最大节点的前一个节点
    auto now = head; //现在遍历的节点的前一个节点
    int len = head->data;
    if(len == 1) {
        goto end;
    }
    for(int i = 0; i < len; i ++) {
        if(now->next->data > pre_max_Node->next->data)
            pre_max_Node = now;
        now = now->next;
    }
    end: pre_max_Node->next = pre_max_Node->next->next;
    head->data --;
}