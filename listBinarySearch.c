#include <stdio.h>
#define MAXSIZE 20
typedef struct AList * List;
struct AList
{
    int data[MAXSIZE];
    int length;
};
int binarySearch(List list,int k){
    int left=0,right=list->length-1;
    int mid;
    int notFound=-1;
    while(left<=right){
        mid = (left + right)/2;
        if(k>list->data[mid]){//k在mid右边   
            left = mid + 1;
        }else if(k==list->data[mid]){
            return mid;
        }else{//k在mid的左边
            right = mid - 1;
        }
    }
    return notFound;
}
int main(){
    struct AList ls = {{1,3,5,10,12,30},6};
    List list = &ls;
    int target = 1;
    int index;
    index = binarySearch(list,target);
    printf("find %d in index %d\n",target,index);
    target = 30;
    index = binarySearch(list,target);
    printf("find %d in index %d\n",target,index);
    target = 31;
    index = binarySearch(list,target);
    printf("find %d in index %d\n",target,index);
}
