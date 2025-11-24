#include <bits/stdc++.h>
using namespace std;

//最少零钱问题
int coinChangeDP(vector<int> &coins, int amt) {
    int n = coins.size();
    int MAX = amt + 1;
    vector<vector<int>> dp (n+1,vector<int> (amt + 1,0));
    for (int i = 1; i <= amt; ++i) {
        dp[0][i] = MAX;
    }
    for (int i = 1; i <= n; ++i) {
        for (int a = 1; a <= amt; ++a) {
            if (a < coins[i-1]) {
                dp[i][a] = dp[i-1][a];
            } else {
                dp[i][a] = min(dp[i-1][a],dp[i][a-coins[i-1]]+1);
            }
        }
    }
    return dp[n][amt] != MAX ? dp[n][amt] : -1;
}

//零钱组合兑换问题
int coinChangeNumDP(vector<int> &coins,int amt) {
    int n = coins.size();
    vector<vector<int>> dp (n + 1,vector<int> (amt+1,1));
    for (int a = 1; a <= amt; ++a) {
        dp[0][a] = 0;
    }
    for (int i = 1; i <= n; ++i) {
        for (int a = 1; a <= amt; ++a) {
            if (a < coins[i-1]) {
                dp[i][a] = dp[i-1][a];
            }else {
                dp[i][a] = dp[i-1][a] + dp[i][a-coins[i-1]];
            }
        }
    }
    return dp[n][amt];
}


int main() {
    vector<int> coins = {1,2,5};
    cout << coinChangeNumDP(coins,5) << endl;
}