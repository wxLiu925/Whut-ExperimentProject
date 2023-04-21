#ifndef _STACK_H
#define _STACK_H

template <class ElemType>
class LinkStack {
private:
    int stacksize; //当前栈大小
    struct Node {
        Node(const ElemType &d = ElemType(), Node *ne = nullptr) : data(d), next(ne) { }
        ElemType data;
        Node *next;
    } *head;
public:
    LinkStack(const int sz = 0) : stacksize(sz){}
    ~LinkStack() {clear();}
    
    void push(ElemType x) {
        Node *p = new Node(x, head);
        head = p;
        stacksize ++;
    }  
    void pop() {
        Node *p = head->next;
        delete head;
        head = p;
        stacksize --;
    }
    ElemType &top() {
        return head->data;
    }
    bool empty() {
        return stacksize == 0;
    }
    int size() {
        return stacksize;
    }
    void clear() {
        while(!empty())
            pop();
    }
};

#endif