#include <iostream>
#include <vector>
//节点信息
typedef struct HNode {
  int weight;
  HNode *lchild, *rchild;
} * Htree;

Htree createHuffmanTree(int arr[], int n) {
    std::vector<Htree> forest(n);
    Htree root = NULL;
    for (int i = 0; i < n; i ++) {  
    //创建一个新节点, 并进行初始化
        Htree temp = new HNode;
        temp->weight = arr[i];
        temp->lchild = temp->rchild = NULL;
        forest[i] = temp;
    }
    for (int i = 1; i < n; i ++) {
        int minn = -1, minnSub;  // minn 为最小值树根下标，minnsub 为次小值树根下标
        //先给minn与minnSub赋一个初值
        for (int j = 0; j < n; j ++) {
            //先对最小值下标minn赋初值
            if (forest[j] != NULL && minn == -1) {
                minn = j;
                continue;
            } //再对次小值下标赋初值
            if (forest[j] != NULL) {
                minnSub = j;
                break;
            }
        }
        //找到当前集合中的最小值下标与次小值下标以便进行合并
        for (int j = minnSub; j < n; j++) {  // 根据 minn 与 minnSub 赋值
            if (forest[j] != NULL) {
                if (forest[j]->weight < forest[minn]->weight) {
                    minnSub = minn;
                    minn = j;
                } else if (forest[j]->weight < forest[minnSub]->weight) {
                    minnSub = j;
                    }
                }
            }
        // 创建一棵新的二叉树, 并对其赋值
        root = new HNode;
        root->weight = forest[minn]->weight + forest[minnSub]->weight;
        root->lchild = forest[minn];
        root->rchild = forest[minnSub];

        forest[minn] = root;     // 指向新树的指针赋给 minn 位置
        forest[minnSub] = NULL;  // minnSub 位置为空
    }
    return root;
}

//计算哈夫曼树的WPL值
int calWPL(Htree root, int len) {
    if (root == NULL)
        return 0;
    else {
        if (root->lchild == NULL && root->rchild == NULL)  // 叶节点
            return root->weight * len;
        else {
            int left = calWPL(root->lchild, len + 1);
            int right = calWPL(root->rchild, len + 1);
            return left + right;
        }
    }
}
//计算哈夫曼编码
void huffmanCoding(Htree root, int len, int arr[]) {
    if (root != NULL) {
        if (root->lchild == NULL && root->rchild == NULL) {
            std::cout << "节点为 " << root->weight << "的字符的编码为: ";
            for (int i = 0; i < len; i ++) {
                std::cout << arr[i] << " \n"[i == len - 1];
            }
        } else {
            arr[len] = 0;
            huffmanCoding(root->lchild, len + 1, arr);
            arr[len] = 1;
            huffmanCoding(root->rchild, len + 1, arr);
        }
    }
}

void test() {
    int a[] = {64, 13, 22, 32, 103, 21, 15, 47, 57, 1, 5, 32, 20, 57, 63, 15, 1, 48, 51, 80, 23, 8, 18, 1, 16, 1};
    auto root = createHuffmanTree(a, 26);
    int ans[26];
    huffmanCoding(root, 0, ans);
}

int main() {
    test();
    return 0;
}