#include <stackTool.h>
Stack createStack(){
    Stack stack = (Stack) malloc(sizeof(struct SNode));
    stack->nextNode=NULL;
    stack->hasLeftParent=0;
    return stack;
}
int isEmpty(Stack stack){
    return stack->nextNode==NULL;
}
void push(Stack stack,char val){
    // stack是头节点Top，后面一个才是真正单元
    // stack->data=val;
    Stack tmp = (Stack) malloc(sizeof(struct SNode));
    tmp->data=val;
    tmp->nextNode = stack->nextNode;
    stack->nextNode=tmp;
}
char pop(Stack stack){
    if(isEmpty(stack)){
        printf("栈空");
        return -1;
    }else{
        Stack nextNode = stack->nextNode;
        char retVal = nextNode->data;
        stack->nextNode = nextNode->nextNode;
        free(nextNode);
        return retVal;
    }
}
void printStack(Stack stack,char buffer[6]){
    for(int i = 0;!isEmpty(stack);i++){
        buffer[i] = stack->nextNode->data;
        stack = stack->nextNode;
    }
}