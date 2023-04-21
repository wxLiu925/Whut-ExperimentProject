#include  <bits/stdc++.h>

//节点信息
template<class T>
struct BtNode {
    T data; //数据域
    BtNode<T> *lchild;
    BtNode<T> *rchild;            
};

template<class T>
class BtTree {
private:
    BtNode<T> *root; //二叉链表

public:
    BtTree() {
        root = nullptr;
    }
    //析构函数遍历销毁二叉树
    ~BtTree() { Destroy_tr(root); }
    void Destroy_tr(BtNode<T>* &p) {
        if(p != nullptr) {
            Destroy_tr(p->lchild);
            Destroy_tr(p->rchild);
            delete p;
            p = nullptr;
        }
    }
    void build_tree(std::string str); //使用括号表示法创建二叉链
    void pre_order() {pre_order(root); } //先序遍历
    void in_order() {in_order(root); } //中序遍历
    void post_order() {post_order(root); } //后序遍历
    void level_order() {level_order(root);} //层次遍历二叉树
    int cal_node() {return cal_node(root); } //计算节点数
    int cal_leaf() {return cal_leaf(root); } //计算叶子节点数
    int cal_high() {return cal_high(root); } //计算树的高度

protected:
    void pre_order(BtNode<T>* &Node)const;
    void in_order(BtNode<T>* &Node)const;
    void post_order(BtNode<T>* &Node)const;
    void level_order(BtNode<T>* &Node)const;
    int cal_node(BtNode<T>* &Node) const;
    int cal_leaf(BtNode<T>* &Node) const;
    int cal_high(BtNode<T>* &Node) const;
};
//使用括号序列创建树
template<class T>
void BtTree<T>::build_tree(std::string str) {
    BtNode<T> *p;
    std::stack<BtNode<T>*> s; //使用树节点指针栈存放
    int k = 0; //1 左儿子  2 右儿子
    for(auto ch: str) { //遍历括号表示
        if(ch == '(') {
            s.push(p);
            k = 1; //处理左孩子
        } else if(ch == ',') {
            k = 2; //处理右孩子
        } else if(ch == ')') {
            s.pop(); //栈顶节点的子树处理完成
        } else {
            p = new BtNode<T>; //创建一个新节点
            p->data = ch; //赋值
            p->lchild = p->rchild = nullptr; //孩子指向空
            if(root == nullptr) root = p; //根节点
            else {
                if(k == 1) s.top()->lchild = p;
                else if(k == 2) s.top()->rchild = p;
            }
        }
    }
}
//前序遍历
template<class T>
void BtTree<T>::pre_order(BtNode<T>*& p) const {
    if(p == nullptr) return;
    std::cout << p->data << " ";
    pre_order(p->lchild);
    pre_order(p->rchild);
}
//中序遍历
template<class T>
void BtTree<T>::in_order(BtNode<T>*& p) const {
    if(p == nullptr) return;
    in_order(p->lchild);
    std::cout << p->data << " ";
    in_order(p->rchild);
}
//后序遍历
template<class T>
void BtTree<T>::post_order(BtNode<T>*& p) const {
    if(p == nullptr) return;
    post_order(p->lchild);
    post_order(p->rchild);
    std::cout << p->data << " ";
}
//层次遍历
template<class T>
void BtTree<T>::level_order(BtNode<T>* &p) const {
    if(p == nullptr) return;
    std::queue<BtNode<T>*> q; //使用树节点指针队列存放
    q.push(p);
    while(!q.empty()) {
        BtNode<T> *np = q.front(); q.pop(); //取出队列首元素
        std::cout << np->data << " ";
        if(np->lchild != nullptr) q.push(np->lchild);
        if(np->rchild != nullptr) q.push(np->rchild);
    }
}

//计算二叉树的节点个数
template<class T>
int BtTree<T>::cal_node(BtNode<T>* &p) const {
    if(p == nullptr) return 0;
    int cnt1 = cal_node(p->lchild); //左子树节点数
    int cnt2 = cal_node(p->rchild); //右子树节点数
    return cnt1 + cnt2 + 1;
}
//计算二叉树的叶子节点个数
template<class T>
int BtTree<T>::cal_leaf(BtNode<T>* &p) const {
    if(p == nullptr) return 0; //考虑一种一边子树为空的情况
    int cnt1 = cal_leaf(p->lchild); //左子树叶子节点数
    int cnt2 = cal_leaf(p->rchild); //右子树叶节子点数
    return cnt1 + cnt2 + (p->lchild == nullptr && p->rchild == nullptr); //为真则答案加1
}
//计算树的高度
template<class T>
int BtTree<T>::cal_high(BtNode<T>* &p) const {
    if(p == nullptr) return 0; //递归终点
    int cnt1 = cal_leaf(p->lchild); //左子树高度
    int cnt2 = cal_leaf(p->rchild); //右子树高度
    return std::max(cnt1 + 1, cnt2 + 1); //左右取最高
}
void test() {
    BtTree<char> *tr = new BtTree<char>;
    std::cout << "输入括号表示法: " << std::endl;
    std::string s; std::cin >> s;
    tr->build_tree(s);
    std::cout << "前序遍历为: ";
    tr->pre_order();
    std::cout << '\n';
    std::cout << "中序遍历为: ";
    tr->in_order();
    std::cout << '\n';
    std::cout << "后序遍历为: ";
    tr->post_order();
    std::cout << '\n';
    std::cout << "层次遍历为: ";
    tr->level_order();
    std::cout << '\n';
    std::cout << "树的节点数: " << tr->cal_node() << '\n';
    std::cout << "树的叶子节点数: " << tr->cal_leaf() << '\n';
    std::cout << "树的高度: " << tr->cal_high() << '\n';
    delete tr;
}

int main() {
    test();
    test();
    return 0;
}