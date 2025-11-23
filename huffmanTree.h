#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
typedef struct HuffmanTreeNode * HuffmanTree;
struct HuffmanTreeNode
{
    int weight;
    HuffmanTree left,right;
};
#endif