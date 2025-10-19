#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct SNode * Stack;
struct SNode{
    char data;
    Stack nextNode;
    int hasLeftParent;
};
Stack createStack();
int isEmpty(Stack stack);
void push(Stack stack,char val);
char pop(Stack stack);
void printStack(Stack stack,char buffer[6]);