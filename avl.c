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

