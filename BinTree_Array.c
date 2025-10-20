#include <stdio.h>
#include <stdlib.h>
#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1
struct TreeNode
{
    ElementType element;
    Tree Left;
    Tree Right;
} T1[MaxTree],T2[MaxTree];

Tree BuildTree(struct TreeNode T[]){
    int nodeNum;
    scanf("%d",&nodeNum);
    if(nodeNum){
        int check[] = (int*) malloc(sizeof(int)*nodeNum);
        for(int i = 0;i<nodeNum;i++) check[i] = 0;
        for(int i = 0;i<nodeNum;i++){
            Tree cl,cr;
            scanf("%c %c %c",&T[i].element,&cl,&cr);
            if(cl!='-'){
                T[i].Left=cl;
                check[cl]=1;
            }else{
                T[i].Left=Null;
            }
            if(cr!='-'){
                T[i].Right=cl;
                check[cr]=1;
            }else{
                T[i].Right=Null;
            }
        }
        int root = -1;
        for(int i = 0;i<nodeNum;i++){
            if(!check[i]){
                root = i;
            }
        }
        return root;
    }
}
int main(){
    Tree R1,R2;
    R1 = BuildTree(T1);
    R2 = BuildTree(T2);
    
}