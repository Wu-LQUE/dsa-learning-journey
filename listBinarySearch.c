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

//不考虑重复元素的二分插入
int binarySearchInsertSimple(int *nums,int size,int target) {
    int i = 0,j = size - 1;
    while (i <= j) {
        int mid = i + (j - i)/2;
        if (nums[mid] < target) {
            i = mid + 1;
        }else if (nums[mid] > target)
        {
            j = mid - 1;
        }else if (nums[mid] == target) {
            return mid;//替换掉target
        }
    }
    //未找到target
    return i;//返回第一个大于target的元素的位置,插入时只需要插到i处，原来的元素后移即可
}

//对于有重复的元素的插入，可以考虑找到一个后，线性地往左边查找，但是效率可能时O(n)，不划算
/*关于该算法：为什么不会“卡住”或“反复横跳”？
每次循环不是 i 变大就是 j 变小（因为 m 介于 i 和 j 之间），区间长度 j - i 严格减小，最多 O(log n) 步。
m 的变化只是区间收缩的结果，虽然它可能先减小后增大，但这不影响单调收缩和最终收敛到 i == 插入点。
维护双闭区间 [i, j]，并保持以下循环不变式：
所有下标 <= i-1(mid) 的元素都严格小于 target；
所有下标 >= j+1(mid) 的元素都大于等于 target；
因此，答案一定落在半闭区间 [i, j+1] 中。
*/
/* 二分查找插入点（存在重复元素） */
int binarySearchInsertion(int *nums, int numSize, int target) {
    int i = 0,j = numSize - 1;
    while (i <= j) {
        int mid = i + (j - i)/2;//mid介于[i,j]之间
        //[i,j](i<=j)不断收缩直至长度为0(i=j)，再下一次循环(i>j<==>i=j+1)就退出，给出返回值i
        if (nums[mid] < target) {
            i = mid + 1;
        }else if (nums[mid] > target) {
            j = mid - 1;
        }else {
            j = mid - 1;
        }
    }
    //全部小于 target（如 [1,2,3], target=10）：i 会一路右推到 n，返回 n，插到末尾
    //返回的是第一个>=target的元素位置
    return i;
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
