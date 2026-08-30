#ifndef BINTREE_H
#define BINTREE_H
typedef struct TreeNode * BinTree;
typedef int TreeNodeDataType;
// typedef BinTree Position;
struct TreeNode{
    int data;
    BinTree left;
    BinTree right;
};
BinTree createBinTree();
BinTree createBinTreeWithData(TreeNodeDataType data);
int getHeight(BinTree bt);
int calculateFactor(BinTree bt);
#endif