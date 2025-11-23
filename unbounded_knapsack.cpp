#include <bits/stdc++.h>
using namespace std;

int unbounded_knapsack(vector<int> wgt,vector<int> val,int cap) {
    int n = wgt.size();
    vector<vector<int>> dp (n+1,vector(cap+1,0));
    for (int i = 1; i <= n; ++i) {
        for (int c = 1; c <= cap; ++c) {
            //容量小于物品重量
            if (c < wgt[i-1]) {
                dp[i][c] = dp[i-1][c];
            }else {
                dp[i][c] = max(dp[i-1][c],dp[i][c-wgt[i-1]]+val[i-1]);
            }
        }
    }
    return dp[n][cap];
}