//P1776 宝物筛选
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 1e5 + 5;
ll dp[MAXN];
ll n,C;
ll w[MAXN],c[MAXN],m[MAXN];
ll new_n;
ll new_w[MAXN],new_c[MAXN],new_m[MAXN];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1776.txt","r",stdin);
    cin >> n >> C;
    for (int i = 1; i <= n; ++i) cin >> w[i] >> c[i] >> m[i];
    //二进制拆分
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m[i]; j<<=1) {
            m[i] -= j;
            new_c[++new_n] = j * c[i];
            new_w[new_n] = j * w[i];
        }
        if (m[i]) {
            new_c[++new_n] = m[i] * c[i];
            new_w[new_n] = m[i] * w[i];
        }
    }
    //滚动数组dp
    for (int i = 1; i <= new_n; ++i) {
        for (int j = C; j >= new_c[i]; --j) {
            dp[j] = max(dp[j],dp[j-new_c[i]]+new_w[i]);
        }
    }
    cout << dp[C] << '\n';
    return 0;
}
