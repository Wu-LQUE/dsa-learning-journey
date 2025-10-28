#include <stdlib.h>
#include <stdio.h>
#define MaxSize 3
typedef struct SNode * Stack;
struct SNode
{
    int data[MaxSize];
    int top = -1;
};
void push(Stack ptrS,int item){
    if(ptrS->top>=MaxSize-1){
        printf("栈满\n");
        return;
    }
    ptrS->data[++(ptrS->top)] = item;
}
int pop(Stack ptrS){
    if(ptrS->top==-1){
        printf("栈空\n");
        return -1;
    }else{
        int item = ptrS->data[(ptrS->top)--];
        return item;
    }
}
int main(){
    Stack stack;
    stack = (Stack) malloc(sizeof(struct SNode));
    stack->top=-1;
    push(stack,1);
    push(stack,2);
    push(stack,3);
    //push(stack,4);
    printf("%d\n",pop(stack));
    printf("%d\n",pop(stack));
    printf("%d\n",pop(stack));
    //printf("%d\n",pop(stack));

}