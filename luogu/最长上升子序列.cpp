#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("最长上升子序列.txt","r",stdin);
    int n; cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    vector<int> dp (n,1);
    //以第i个数结尾的序列的最大上升子序列长度
    for (int i = 0; i < n; ++i) {
        //前i-1个数中最大上升子序列长度及其最大值
        for (int j = 0; j < i; ++j) {
            if (arr[i] > arr[j]) {
                dp[i] = max(dp[i],dp[j]+1);
            }
        }
    }
    int maxLen=0;
    for (int &num : dp) {
        maxLen = max(maxLen,num);
    }
    cout << maxLen << endl;
}