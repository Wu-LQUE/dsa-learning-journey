#include <bits/stdc++.h>
using namespace std;

//前缀和，一次预处理，多次查询
int main() {
    vector<int> nums (10);
    for (int i = 0; i < nums.size(); ++i) {
        nums[i] = i + 1;
    }
    vector<int> prefixSum (nums.size());
    partial_sum(nums.begin(),nums.end(),prefixSum.begin());
    for (int i : prefixSum) {
        cout << i << " ";
    }
    cout << endl;
}