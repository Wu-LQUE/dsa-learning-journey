#include <bits/stdc++.h>
using namespace std;
void merge(vector<int> &nums,int left,int mid,int right) {
    //左子数组的区间为[left,mid],右边是[mid+1,right]
    //存储结果
    vector<int> tmp(right - left +1);
    //初始化左子数组和右边的起始索引
    int i = left,j = mid + 1,k = 0;
    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j]) {
            tmp[k++] = nums[i++];
        }else {
            tmp[k++] = nums[j++];
        }
    }
    // 将左子数组和右子数组的剩余元素复制到临时数组中
    while (i <= mid) {
        tmp[k++] = nums[i++];
    }
    while (j <= right) {
        tmp[k++] = nums[j++];
    }
    for (k = 0; k < tmp.size();++k) {
        nums[left + k] = tmp[k];
    }
}

//归并排序
void mergeSort(vector<int> &nums,int left,int right) {
    if (left >= right) return;//当子数组长度为1时终止递归
    int mid = left + (right - left)/2;
    mergeSort(nums,left,mid);
    mergeSort(nums,mid+1,right);
    //合并阶段
    merge(nums,left,mid,right);
}
//todo，链表优化