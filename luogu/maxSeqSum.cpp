#include <bits/stdc++.h>
using namespace std;

//最大子列和
int solve(vector<int> &arr) {
    int n = arr.size();
    vector<int> dp(n);
    //以第1个数结尾的序列的最大子列和
    for (int i = 0; i < n; ++i) {
        if (i==0) dp[i] = arr[i];
        dp[i] = max(arr[i],arr[i]+dp[i-1]);
    }
    int maxSum = INT_MIN;
    for (int i = 0; i < n; ++i) {
        maxSum = max(maxSum,dp[i]);
    }
    return maxSum;
}

int main() {
    //io加速
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    freopen("maxSeqSum.txt","r",stdin);
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    cout << solve(nums) << endl;
    return 0;
}