//P1616 疯狂的采药
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 10e7+5;
ll w[MAXN];
ll v[MAXN];
ll t,m;
ll dp[MAXN];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1616.txt","r",stdin);
    cin >> t >> m;
    for (int i = 1; i <= m; ++i) cin >> w[i] >> v[i];
    for (int i = 1; i <= m; ++i)
        for (int j = w[i]; j <= t; ++j)
            dp[j] = max(dp[j],dp[j-w[i]] + v[i]);
    cout << dp[t] << '\n';
    return 0;
}
