//选择排序：O(n^2)，非稳定排序(相同元素的相对顺序可能改变)
void selectionSort(int nums[],int n) {
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (nums[j] < nums[minIndex]) {
                minIndex = j;
            }
        }
        // int minData = nums[minIndex];
        // nums[minIndex] = nums[i];
        // nums[i] = minData;
        int tmp = nums[i];
        nums[i] = nums[minIndex];
        nums[minIndex] = tmp;
    }
}
//冒泡排序:优化版(如果某轮没有做交换，则说明有序，提前终止)
void bubbleSort(int nums[],int n) {
    for (int i = 0; i < n; ++i) {
        int swapped = 0;  // 优化：记录是否发生交换
        for (int j = 0; j < n - i - 1; ++j) {
            if (nums[j] > nums[j+1]) {
                int tmp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = tmp;
                swapped = 1;
            }
        }
        if (swapped==0) {
            break;
        }
    }
}

//插入排序
void insertionSort(int nums[],int n) {
    for (int i = 1; i < n; ++i) {
        int base = nums[i];
        int j = i - 1;
        while (j >=0 && nums[j] > base) {
            nums[j+1] = nums[j];
            j--;
        }
        nums[j+1] = base;
    }
}

void swap(int *i,int *j) {
    if (i==j) return;
    int tmp = *i;
    *i = *j;
    *j = tmp;
}

//快速排序
int partition(int nums[],int left,int right) {
    int i =left,j = right;
    //只要i,j不相遇，就一直做交换，把小于基准的数放左边，大于基准的放右边
    //相当于做一个双向的过滤，交换
    //目的:左边<=基准<=右边

    //两个while的顺序不能改变，首先保证第一轮交换不会把大数换到左边
    //其次保证i<j条件被破坏时，无论是j碰到i还是i碰到j，这个数都是一个<=基准数的数
    while (i < j) {
        //找出第一个比基准数小的数
        while (i < j && nums[j] >= nums[left]) {
            j--;
        }
        //找出第一个比基准数大的数
        while (i < j && nums[i] <= nums[left]) {
            i++;
        }
        //交换
        swap(&nums[i],&nums[j]);
    }
    swap(&nums[left],&nums[i]);
    return i;
}

//初始调用left = 0, right = n - 1
void quickSort(int nums[],int left,int right) {
    if (left >= right) return;
    int pivot = partition(nums,left,right);
    quickSort(nums,left,pivot-1);
    quickSort(nums,pivot+1,right);
}

//对哨兵选择的优化
int medianThree(int nums[],int i,int j,int k) {
    int a = nums[i],b=nums[j],c=nums[k];
    if ((a <= b && b <=c) || (c <= b && b <=a)) return j;
    else if ((b <= a && a <= c)||(c <= a && a <= b)) return i;
    else return k;
}

int medianPartition(int nums[],int left,int right) {
    int mid = (left + right)/2;
    int base = medianThree(nums,left,mid,right);
    swap(&nums[left],&nums[base]);
    int i = left,j = right;
    while (i < j) {
        while (i < j && nums[j] >= nums[left]) {
            j--;
        }
        while (i < j && nums[i] <= nums[left])
        {
            i++;
        }
        swap(&nums[i],&nums[j]);
    }
    swap(&nums[left],&nums[i]);
    return i;
}

//优化的快速排序
void refinedQuickSort(int nums[],int left,int right) {
    if (left >= right) return;
    int pivot = medianPartition(nums,left,right);
    refinedQuickSort(nums,left,pivot-1);
    refinedQuickSort(nums,pivot+1,right);
}

//空间优化
void quickSortTailCall(int nums[],int left,int right) {
    while (left < right) {
        int privot = medianPartition(nums,left,right);
        if (privot - left < right - privot) {
            quickSortTailCall(nums,left,privot-1);
            left = privot + 1;
        }else {
            quickSOrtTailCall(nums,privot + 1,right);
            right = privot - 1;
        }
    }
}