#include "set.h"
int findRoot(SetType set[],ElementType x){
    int i;
    for(i=0;i<setMaxSize;i++){
        if(set[i].data==x) break;
    }
    if(i>=setMaxSize) return -1;
    for(;set[i].parent>=0;i = set[i].parent);
    return i;
}
void unionSet(SetType set[],ElementType x1,ElementType x2){
    int r1 = findRoot(set,x1);
    int r2 = findRoot(set,x2);
    //将小的集合合并到大的集合中去
    if(set[r1].data < set[r2].data) set[r2].parent = r1;
    else set[r1].parent = r2;
}