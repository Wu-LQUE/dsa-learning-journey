#ifndef AVL_H
#define AVL_H

#include "BinTree.h"

// 将值 x 插入到 AVL 树 root 中，返回（可能更新后的）新根节点
BinTree avl_insert(BinTree root, TreeNodeDataType x);

#endif // AVL_H