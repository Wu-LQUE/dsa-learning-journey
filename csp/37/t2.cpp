#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e4+10;
const int NN = 105;
ll n,m;
ll v[NN];
ll dp[N];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t2.txt","r",stdin);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) { cin >> v[i]; }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i >= j) dp[i] = max(dp[i],dp[i-j]+v[j]);
        }
    }
    cout << dp[n] << endl;
}