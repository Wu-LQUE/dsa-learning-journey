#include "stackTool.h"
Stack createStack(){
    Stack stack = (Stack) malloc(sizeof(struct SNode));
    stack->nextNode=NULL;
    return stack;
}
int isEmpty(Stack stack){
    return stack->nextNode==NULL;
}
void push(Stack stack,ElementType val){
    // stack是头节点Top，后面一个才是真正单元
    // stack->data=val;
    Stack tmp = (Stack) malloc(sizeof(struct SNode));
    tmp->data=val;
    tmp->nextNode = stack->nextNode;
    stack->nextNode=tmp;
}
ElementType pop(Stack stack){
    if(isEmpty(stack)){
        printf("栈空");
        return NULL;
    }else{
        Stack nextNode = stack->nextNode;
        ElementType retVal = nextNode->data;
        stack->nextNode = nextNode->nextNode;
        free(nextNode);
        return retVal;
    }
}
ElementType getTop(Stack stack){
    ElementType data = pop(stack);
    push(stack,data);
    return data;
}
void printStack(Stack stack){
    for(int i = 0;!isEmpty(stack);i++){
        printf("%d",stack->nextNode->data->data);//根据类型调整
        stack = stack->nextNode;
    }
}