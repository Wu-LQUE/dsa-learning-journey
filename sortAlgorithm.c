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