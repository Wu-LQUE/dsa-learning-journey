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