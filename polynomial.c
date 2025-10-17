//多项式处理
#include <stdio.h>
#include <stdlib.h>
#define ERROR 114514;
typedef struct APolyNode * PolyNode; 
typedef struct APolyNode * Polynomial; 
struct APolyNode
{
    int coef;//系数coefficient 
    int expon;//指数
    PolyNode nextNode;
};
void attach(int coef,int expon,PolyNode *pRear){
    //增加并修改末尾指针
    PolyNode last = (PolyNode) malloc(sizeof(struct APolyNode));
    last->coef=coef;
    last->expon=expon;
    last->nextNode=NULL;
    (*pRear)->nextNode=last;
    *pRear=last;
}
int compareExpon(PolyNode p1,PolyNode p2){
    int result;
    if(!(p1&&p2)){
        printf("有空节点");
        return ERROR;
    }
    if(p1->expon>p2->expon){
        result=1;
    }else if(p1->expon==p2->expon){
        result=0;
    }else{
        result=-1;
    }
    return result;
}
Polynomial addPoly(Polynomial p1,Polynomial p2){
    PolyNode front,rear,tmp;
    int sum;
    rear = (PolyNode) malloc(sizeof(struct APolyNode));
    front = rear;//拷贝一个空的首项的指针，因为rear会指向最后一个
    int sumCoef;
    while(p1&&p2){
        switch (compareExpon(p1,p2))
        {
        case 0:
            //指数一样
            sumCoef = p1->coef+p2->coef;
            if(sumCoef) attach(sumCoef,p1->expon,&rear);
            p1=p1->nextNode;
            p2=p2->nextNode;
            break;
        case 1:
            //p1的指数更高
            attach(p1->coef,p1->expon,&rear);
            p1=p1->nextNode;
            break;
        case -1:
            //p2的指数更高
            attach(p2->coef,p2->expon,&rear);
            p2=p2->nextNode;
            break;
        default:
            break;
        }
    }
    //p1或者p2肯定有一个空了，把没空的后面每一项都加到后面去
    for(;p1;p1=p1->nextNode) attach(p1->coef,p1->expon,&rear);
    for(;p2;p2=p2->nextNode) attach(p2->coef,p2->expon,&rear);
    rear->nextNode=NULL;
    tmp = front->nextNode;
    free(front);
    return tmp;
}
Polynomial readPoly(){
    int pairNum;
    scanf("%d",&pairNum);//读入多项式项数
    int coef,expon;
    Polynomial front,rear,tmp;
    rear = (PolyNode) malloc(sizeof(struct APolyNode));
    rear->nextNode=NULL;
    front = rear;
    while(pairNum--){
        scanf("%d %d",&coef,&expon);//成对读入每项的系数和指数
        attach(coef,expon,&rear);
    }
    tmp = front->nextNode;
    free(front);
    return tmp;
}
void printPoly(Polynomial p){
    PolyNode pNode = p;
    int isFirst = 1;
    for(;pNode;pNode=pNode->nextNode){
        if(isFirst){
            isFirst=0;
        }else{
            pNode->coef >=0 ? printf(" + ") : printf(" - ");
        }
        if(pNode->expon==0){
            printf("%d",pNode->coef);
        }else{
            printf("%dx^%d",pNode->coef >= 0 ? pNode->coef : -pNode->coef ,pNode->expon);
        }
    }
    printf("\n");
}
Polynomial multiPoly(Polynomial p1,Polynomial p2){
    //先算p1[1]*p2，后面的结果再插入进去
    PolyNode currP1 = p1;
    PolyNode currP2 = p2;
    PolyNode result = (PolyNode) malloc(sizeof(struct APolyNode));
    PolyNode front = result;
    result->coef=0;
    result->expon=0;
    result->nextNode=NULL;
    if(!(p1&&p2)){
        printf("有一项多项式为空");
        return result;
    }
    //p1[1]*p2
    while (currP2){
        attach(currP1->coef*currP2->coef,currP1->expon+currP2->expon,&result);
        currP2=currP2->nextNode;
    }
    currP1=currP1->nextNode;
    while (currP1)
    {
        currP2=p2;
        PolyNode insertPos = front;
        while (currP2){
            // attach(currP1->coef*currP2->coef,currP1->expon+currP2->expon,&result);
            int coef = currP1->coef*currP2->coef;
            int expon = currP1->expon+currP2->expon;
            //找到要插入的位置,insert指向的下一项指数<=当前项
            while(insertPos->nextNode&&insertPos->nextNode->expon > expon){
                insertPos = insertPos->nextNode;
            }
            if(insertPos->nextNode&&insertPos->nextNode->expon==expon){//指数一致做合并
                insertPos->nextNode->coef+=coef;
                if(!insertPos->nextNode->coef){//系数抵消了
                    PolyNode tmp = insertPos->nextNode;
                    insertPos->nextNode=tmp->nextNode;
                    free(tmp);
                }
            }else{//指数更小或者后面没有项了，直接插入
                PolyNode tmp = (PolyNode) malloc(sizeof(struct APolyNode));
                tmp->coef = coef;
                tmp->expon = expon;
                tmp->nextNode = insertPos->nextNode;
                insertPos->nextNode=tmp;
                insertPos=tmp;
            }
            currP2=currP2->nextNode;
        }
        currP1=currP1->nextNode;
    }
    PolyNode tmp = front->nextNode;
    free(front);
    return tmp;
}
int main(){
    freopen("polytest.txt","r",stdin);
    Polynomial p1 = readPoly();
    printf("inputP1:\t");
    printPoly(p1);
    Polynomial p2 = readPoly();
    printf("inputP2:\t");
    printPoly(p2);
    Polynomial polyAddResult = addPoly(p1,p2);
    printf("P1+P2:\t\t");
    printPoly(polyAddResult);
    Polynomial polyMultiResult = multiPoly(p1,p2);
    printf("P1*P2:\t\t");
    printPoly(polyMultiResult);
}
