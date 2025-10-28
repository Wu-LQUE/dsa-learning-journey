#include <stdio.h>
#define MAXSIZE 20
typedef struct AList * List;
struct AList
{
    int data[MAXSIZE];
    int length;
};
int binarySearch(List list,int k){
    // 初始化双闭区间 [0, n-1] ，即 left, right 分别指向数组首元素、尾元素
    int left=0,right=list->length-1;
    int mid;
    int notFound=-1;
    while(left<=right){
        /*值得注意的是，由于left和right都是 int 类型，因此可能会超出 int 类型的取值范围。
        为了避免大数越界，我们通常采用公式left + (right-left)/2来计算中点。*/
        mid = left + (right - left)/2;
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

//同样还有左闭右开区间的写法，i=0,j=n [i,j),终止条件是i>=j，
//但这种写法不大对称，还是双闭区间的写法不容易出错
int binarySearchLeftCloseRightOpen(List list,int target) {
    int i = 0,j = list->length;
    int mid;
    while (i < j) {
        mid = i + (j - i)/2;
        if (list->data[mid] < target) {
            //在[mid+1,j)
            i = mid + 1;
        }else if (list->data[mid] == target) {
            return mid;
        }else if (list->data[mid] > target) {
            //在[i,mid)
            j = mid;
        }
    }
    return -1;
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
