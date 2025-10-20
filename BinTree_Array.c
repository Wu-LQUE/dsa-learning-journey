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
    //不要少了\n!!!!!这个不读会有奇奇怪怪的报错
    scanf("%d\n",&nodeNum);
    int root = Null;
    if(nodeNum){
        // int *check = (int*) malloc(sizeof(int)*nodeNum);
        int check[8];
        for(int i = 0;i<nodeNum;i++) check[i] = 0;
        for(int i = 0;i<nodeNum;i++){
            char cl,cr;
            scanf("%c %c %c\n",&T[i].element,&cl,&cr);
            if(cl!='-'){
                cl = cl - '0';
                T[i].Left=cl;
                check[cl]=1;
            }else{
                T[i].Left=Null;
            }
            if(cr!='-'){
                cr = cr - '0';
                T[i].Right=cr;
                check[cr]=1;
            }else{
                T[i].Right=Null;
            }
        }
        for(int i = 0;i<nodeNum;i++){
            if(!check[i]){
                root = i;
            }
        }
    }
    return root;
}
int IsOmophic(Tree R1, Tree R2){
    if(R1 == Null && R2 == Null) 
        return 1;
    if((R1 == Null && R2 != Null) || (R1 != Null && R2 == Null)) 
        return 0;
    if(T1[R1].element != T2[R2].element) 
        return 0;
    
    // 不交换左右子树的情况
    if(IsOmophic(T1[R1].Left, T2[R2].Left) && IsOmophic(T1[R1].Right, T2[R2].Right))
        return 1;
    
    // 交换左右子树的情况
    if(IsOmophic(T1[R1].Left, T2[R2].Right) && IsOmophic(T1[R1].Right, T2[R2].Left))
        return 1;
    
    return 0;
}
int main(){
    Tree R1,R2;
    freopen("BinTree_Array_test.txt","r",stdin);
    R1 = BuildTree(T1);
    R2 = BuildTree(T2);
    printf("%d",IsOmophic(R1,R2));
}