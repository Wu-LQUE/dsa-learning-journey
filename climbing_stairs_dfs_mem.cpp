#include <bits/stdc++.h>
using namespace std;

int dfs(int n,vector<int> &mem) {
    if (n == 1 || n == 2) return n;
    if (mem[n]!=-1) return mem[n];
    int count =  dfs(n-2,mem) + dfs(n-1,mem);
    mem[n] = count;
    return count;
}

/* 爬楼梯：记忆化搜索 */
int climbingStairsDFSMem(int n) {
    // mem[i] 记录爬到第 i 阶的方案总数，-1 代表无记录
    vector<int> mem(n + 1, -1);
    return dfs(n, mem);
}
int climbingStairsDP(int n) {
    if (n == 1 || n == 2) return n;
    vector<int> dp(n+1);
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= n; ++i) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}


//无后效性是动态规划能够有效解决问题的重要特性之一，其定义为：给定一个确定的状态，它的未来发展只与当前状态有关，而与过去经历的所有状态无关。

/* 爬楼梯最小代价：动态规划 */
int minCostClimbingStairsDP(vector<int> &cost) {
    int n = cost.size() - 1;
    if (n == 1 || n == 2) {
        return cost[n];
    }
    // vector<int> dp(n);
    // dp[1] = cost[1];
    // dp[2] = cost[2];
    // for (int i=3; i <= n; ++i) {
    //     dp[i] = min(dp[i-1],dp[i-2]) + cost[i];
    // }
    //做一个空间的优化
    int last2 = cost[1];
    int last1 = cost[2];
    for (int i = 3; i <= n; ++i) {
        int tmp = last1;
        last1 = min(last1,last2) + cost[i];
        last2 = tmp;
    }
    return last1;
}

//给定一个共有n阶的楼梯，你每步可以上1阶或者2阶，但不能连续两轮跳 
//1阶，请问有多少种方案可以爬到楼顶？
//这是有约束条件的动态规划，需要带上一个状态的动态转移条件
/* 带约束爬楼梯：动态规划 */
int climbingStairsConstraintDP(int n) {
    if (n == 1 || n == 2) {
        return 1;
    }
    //我们使用[i,j],i代表到这一个台阶，j=1/2代表上一个状态走了几步到这
    vector<vector<int>> dp (n+1,vector<int> (3));
    dp[1][1] = 1;
    dp[1][2] = 0;
    dp[2][1] = 0;
    dp[2][2] = 1;
    for (int i = 3; i <= n; ++i) {
        dp[i][1] = dp[i-1][2];
        dp[i][2] = dp[i-2][1] + dp[i-2][2];
    }
    return dp[n][1] + dp[n][2];
}

int main() {
    int n = 40;
    cout << climbingStairsDFSMem(n) << endl;
    cout << climbingStairsDP(n) << endl;
    vector<int> cost = {0,1,10,1,4,9};
    cout << minCostClimbingStairsDP(cost) << endl;
    return 0;
}