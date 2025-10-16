#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct SNode * Stack;
struct SNode{
    char data;
    Stack nextNode;
    int hasLeftParent;
};
Stack createStack(){
    Stack stack = (Stack) malloc(sizeof(struct SNode));
    stack->nextNode=nullptr;
    stack->hasLeftParent=0;
    return stack;
}
int isEmpty(Stack stack){
    return stack->nextNode==nullptr;
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
int isOperand(char ch){
    if('0'<=ch&&ch<='9'){
        return 1;
    }else if (('a'<=ch&&ch<='z')||('A'<=ch&&ch<='Z')){
        return 1;
    }
    return 0;
}

int isOperator(char ch){
    if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='('||ch==')'){
        return 1;
    }
    return 0;
}
void printStack(Stack stack,char buffer[6]){
    for(int i = 0;!isEmpty(stack);i++){
        buffer[i] = stack->nextNode->data;
        stack = stack->nextNode;
    }
}
void reverseStr(char *str){
    int len = strlen(str);
    for(int i = 0;i<len/2;i++){
        char ch = str[i];
        str[i] = str[len-1-i];
        str[len-1-i] = ch;
    }
}
struct OperatorPriority {
    int add;
    int sub;
    int multiply;
    int div;
    int leftParent;
    OperatorPriority() : add(0), sub(0), multiply(1), div(1), leftParent(-1) {}
};
int getPriority(OperatorPriority *opMap,char op){
    if(op=='+') return opMap->add;
    if(op=='-') return opMap->sub;
    if(op=='*') return opMap->multiply;
    if(op=='/') return opMap->div;
    if(op=='(') return opMap->leftParent;
    return -100;
}
int isGreaterThan(OperatorPriority *opMap,char a,char b){
    return getPriority(opMap,a) > getPriority(opMap,b);
}
int isEqual(OperatorPriority *opMap,char a,char b){
    return getPriority(opMap,a) == getPriority(opMap,b);
}

int main(){
    Stack stack = createStack();
    OperatorPriority *opMap = new OperatorPriority();
    char ch;
    while((ch = getchar())!='\n'){
        char buffer[6]={'\0'};
        printStack(stack,buffer);
        reverseStr(buffer);
        // printf(" stack:%s\n",buffer);
        if(ch==' '||ch=='\t'){
            continue;
        }else if(isOperand(ch)){
            printf("%c",ch);
            continue;
        }else if(isOperator(ch)){
            if(isEmpty(stack)){
                if(ch=='(') stack->hasLeftParent+=1;
                push(stack,ch);
                continue;
            }else{
                int hasLeftParent = stack->hasLeftParent;
                char currOp = ch;
                //有右边括号，运算符全部出栈
                if (currOp=='('){
                    push(stack,currOp);
                    stack->hasLeftParent+=1;
                    continue;
                }else if(currOp==')'&&hasLeftParent){
                    char tmp;
                    while((tmp=pop(stack))!='('){
                        printf("%c",tmp);
                    }
                    stack->hasLeftParent-=1;
                    continue;
                }
                char lastOp = pop(stack);
                if(isGreaterThan(opMap,currOp,lastOp)){
                    push(stack,lastOp);
                    push(stack,currOp);
                    continue;
                }else{
                    printf("%c",lastOp);
                    if(isEmpty(stack)){
                        push(stack,currOp);
                        continue;;
                    }
                    while(!isEmpty(stack)){
                        lastOp=pop(stack);
                        if(isGreaterThan(opMap,currOp,lastOp)){
                            push(stack,lastOp);
                            push(stack,currOp);
                            break;
                        }else{
                            printf("%c",lastOp);
                        }
                    }
                    if(isEmpty(stack)){
                        push(stack,currOp);
                        continue;;
                    }
                }
            }
        }
    }
    
    while(!isEmpty(stack)){
        char op=pop(stack);
        printf("%c",op);
    }

    printf("\n");

    free(opMap);
    free(stack);
}