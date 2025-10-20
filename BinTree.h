#ifndef BINTREE_H
#define BINTREE_H
typedef struct TreeNode * BinTree;
// typedef BinTree Position;
struct TreeNode{
    int data;
    BinTree left;
    BinTree right;
};
#endif