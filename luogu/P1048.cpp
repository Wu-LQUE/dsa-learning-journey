//P1048 [NOIP 2005 普及组] 采药
//恰好装满的初始化方式
// memset(dp,-0x3f,sizeof(dp));
// dp[0] = 0;
// cout << dp[t] << '\n';

//不超过背包容量
//恰好装满 + 直接输出	dp[0]=0，其余 -inf	dp[t]	必须恰好装满	❌ 不符合题意
//不超过容量 + 直接输出	全部 0	dp[t]
#include <bits/stdc++.h>
using namespace std;
#define ll long long
//const int MAXN = 2e6 + 5;
int w[105];
int v[105];
// int dp[105][1005];
int dp[1005];
ll t,m;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1048.txt","r",stdin);
    memset(dp,-0x3f,sizeof(dp));
    dp[0] = 0;
    cin >> t >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> w[i] >> v[i];
    }
    // for (int i = 1; i <= m; ++i) {
    //     for (int j = 0; j <= t; ++j) {
    //         if (j < w[i]) dp[i][j] = dp[i-1][j];
    //         else dp[i][j] = max(dp[i-1][j],dp[i-1][j-w[i]]+v[i]);
    //     }
    // }
    // cout << dp[m][t] << '\n';
    for (int i = 1; i <= m; ++i) {
        for (int j = t; j >= w[i]; --j) {
            dp[j] = max(dp[j],dp[j-w[i]]+v[i]);
        }
    }
    cout << dp[t] << '\n';
    return 0;
}
