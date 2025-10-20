#ifndef STACKTOOL_H
#define STACKTOOL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//第一个节点是Top，空的,stack->nextNode才是第一个值
#include "BinTree.h"
typedef BinTree ElementType; 
typedef struct SNode * Stack;
struct SNode{
    ElementType data;
    Stack nextNode;
};
Stack createStack();
int isEmpty(Stack stack);
void push(Stack stack,ElementType val);
ElementType pop(Stack stack);
void printStack(Stack stack);
#endif