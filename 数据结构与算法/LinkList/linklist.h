#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#undef NULL 
#if defined(__cplusplus)
#define NULL 0
#else
#define NULL ((void *)0)
#endif
class LinkNode {
#define ElemType int //链表中数据域的数据类型, 方便修改
private:
    struct Node {
        ElemType data; //数据域 
        Node *next; //指针域
        Node(ElemType dat) : data(dat), next(NULL){}
    } *head; //头节点
public:
    LinkNode(){Initlist();}
    ~LinkNode() {}
    void Initlist(); //初始化单链表L，建立一个带头结点的单链表
    int ListLength(); //返回单链表L的长度
    void ListInsert(int i, ElemType e); //在单链表L的第i个位置上插入元素e
    void ListDelete(int i); //删除单链表L的第i个元素
    void DispList(); //输出单链表L
    void CreateListT(ElemType A[], int n); //头插法建表L
    void DelMaxNode(); //删除单链表中元素值最大的结点
};

#endif