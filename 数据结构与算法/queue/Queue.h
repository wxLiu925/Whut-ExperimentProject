#ifndef _QUEUE_H
#define _QUEUE_H

template <class ElemType>
class LinkQueue {
private:
    int queuesize;
    struct Node {
        Node(const ElemType &d = ElemType(), Node *ne = nullptr) : data(d), next(ne) { }
        ElemType data;
        Node *next;
    } *front, *rear;
public:
    LinkQueue() : front(nullptr), rear(nullptr) , queuesize(0){}
    ~LinkQueue() {clear();}
    void enqueue(const ElemType x) {
        Node *p = new Node(x);
        if (rear != nullptr)
            rear = rear->next = p;
        else
            front = rear = p;
        queuesize ++;
    }
    void dequeue() {
        Node *p = front;
        if (front->next == nullptr)
            front = rear = nullptr;
        else
            front = front->next;
        delete p;
        if(queuesize > 0) queuesize --;
    }
    ElemType Front() {
        return front->data;
    }
    bool empty() {
        return front == nullptr;
    }
    int size() {
        return queuesize;
    }
    void clear() {
        while (front != nullptr)
            dequeue();
        queuesize = 0;
    }
};
#endif