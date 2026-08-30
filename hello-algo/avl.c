#include "avl.h"
#include <stdlib.h>

//将root左旋
static BinTree rotateLeft(BinTree root){
    BinTree newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    return newRoot;
}
//将root右旋
static BinTree rotateRight(BinTree root){
    BinTree newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    return newRoot;
}

//将avl插入,BST正常插入，在自底向上调整
BinTree avl_insert(BinTree root, TreeNodeDataType x){
    if(!root){
        //返回创建的新节点
        return createBinTreeWithData(x);
    }
    if(x < root->data){
        root->left = avl_insert(root->left,x);
    }else if (x > root->data)
    {
        root->right = avl_insert(root->right,x);
    }else{
        return root;//相等，无需插入
    }
    
    int balanceFactor = calculateFactor(root);
    if(balanceFactor > 1 && x < root->left->data){
        //左子树高，x在左子树的左边，LL型
        return rotateRight(root);
    }else if (balanceFactor > 1 && x > root->left->data)
    {
        //左子树高，但x在左子树的右边，LR 型
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }else if (balanceFactor < -1 && x > root->right->data)
    {
        //RR型
        return rotateLeft(root);
    }else if(balanceFactor < -1 && x < root->right->data){
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    
    //无需旋转，直接返回 
    return root;
}

/* 删除接口：必须把返回的根写回 tree->root */
void removeItem(BinTree tree, int val) {
    if (tree == NULL) return;
    tree = removeHelper(tree, val);
    /* 如果你维护 size，需要在 removeHelper 中或这里判断是否确实删除了节点并相应减一 */
}

/* 递归删除节点（辅助函数） */
BinTree*removeHelper(BinTree node, int val) {
    if (node == NULL) {
        return NULL;
    }

    if (val < node->data) {
        node->left = removeHelper(node->left, val);
    } else if (val > node->data) {
        node->right = removeHelper(node->right, val);
    } else {
        /* 找到要删除的节点 */
        if (node->left == NULL || node->right == NULL) {
            /* 0 或 1 个子节点 */
            BinTree child = node->left ? node->left : node->right;
            if (child == NULL) {
                /* 无子节点：释放并返回 NULL */
                free(node);
                return NULL;
            } else {
                /* 一个子节点：用该子节点替代当前节点，释放当前节点 */
                BinTree temp = node;
                node = child;
                free(temp);
            }
        } else {
            /* 两个子节点：用右子树最小节点（中序后继）替换，然后删除后继 */
            BinTree succ = node->right;
            while (succ->left != NULL) succ = succ->left;
            node->data = succ->data; /* 复制值 */
            /* 从右子树删除该后继节点 */
            node->right = removeHelper(node->right, succ->data);
        }
    }

    /* node 可能因为删除而变为 NULL（上面返回了 NULL 的情况已处理），在这里确保非 NULL */
    if (node == NULL) return NULL;

    /* 更新高度并旋转以恢复 AVL 平衡 */
    updateHeight(node);
    return rotate(node);
}