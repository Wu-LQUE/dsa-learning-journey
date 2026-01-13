#include "chaining_hash_map.h"
//借助hashMap(data->index),检查target - nums[i](data)的索引(index)在不在hashMap中，
//如果不在，将它加入hashMap,如果在里面，那么直接返回i和找到的索引
//传入returnNums是指针，会被被调用者malloc修改，调用者free;returnSize不为NULL
int *findTwoSum(int *nums,int numSize,int target,int *returnSize) {
    if (!nums || numSize <= 0 || returnSize == NULL) return NULL;
    HashMapChaining *hashMap = newHashMapChaining();
    for (int i = 0; i < numSize; ++i) {
        int rest = target - nums[i];
        int isInKeySet = inKeySet(hashMap,rest);
        if (isInKeySet == 1) {
            int *res = (int *)malloc(sizeof(int)*2);
            res[0] = *get(hashMap,rest);
            res[1] = i;
            *returnSize = 2;
            return res;
            delHashMapChaining(hashMap);
        }
        put(hashMap,nums[i],&i);
    }
    delHashMapChaining(hashMap);
    return NULL;

}
int main() {
    int nums[]={2,7,11,15};
    int returnSize;
    int *retNums = findTwoSum(nums,4,13,&returnSize);
    
    return 0;
}