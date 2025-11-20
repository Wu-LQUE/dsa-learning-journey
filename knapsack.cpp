#include <bits/stdc++.h>
using namespace std;

/* 0-1 背包：暴力搜索 */
int knapsackDFS(vector<int> &wgt, vector<int> &val,vector<vector<int>> &mem, int i, int c) {
    //空背包或0容量
    if (i == 0 || c == 0) {
        return 0;
    }
    // 若已有记录，则直接返回
    if (mem[i][c] != -1) {
        return mem[i][c];
    }
    // 若超过背包容量，则只能选择不放入背包
    if (wgt[i-1] > c) {
        mem[i][c] = knapsackDFS(wgt,val,mem,i-1,c);
        return mem[i][c];
    }else {
        //重量不变，到上一个
        int no = knapsackDFS(wgt,val,mem,i-1,c);
        //减去重量后搜索上一个
        int yes = knapsackDFS(wgt,val,mem,i-1,c-wgt[i-1])+val[i-1];
        // 记录并返回两种方案中价值更大的那一个
        mem[i][c] = max(no, yes);
        return mem[i][c];
    }
}

int knapsackDP(vector<int> &wgt,vector<int> &val,int cap) {
    int n = wgt.size();
    vector<vector<int>> dp(n+1,vector<int> (cap+1,0));
    for (int i = 1; i <=n; ++i) {
        for (int c = 1; c <=cap; ++c) {
            //当前物品超重
            if (wgt[i-1] > c) {
                dp[i][c] = dp[i-1][c];
            }else{
                dp[i][c] = max(dp[i-1][c], dp[i-1][c-wgt[i-1]] + val[i-1]);
            }
        }
    }
    return dp[n][cap];
}

//倒序遍历做空间优化
int knapsackDPMemRefine(vector<int> &wgt,vector<int> &val,int cap) {
    int n = wgt.size();
    vector<int> dp(cap+1,0);
    for (int i = 1; i <=n; ++i) {
        for (int c = cap; c >=1; --c) {
            // //当前物品超重
            // if (wgt[i-1] > c) {
            //     dp[c] = dp[c];
            // }else{
            //     dp[c] = max(dp[c], dp[c-wgt[i-1]] + val[i-1]);
            // }
            //当前物品超重
            if (wgt[i-1] <= c) {
                dp[c] = max(dp[c], dp[c-wgt[i-1]] + val[i-1]);
            }
        }
    }
    return dp[cap];
}

int main( ) {

}