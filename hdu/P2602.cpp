#include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
using namespace std;
#define ll long long

ll dp[1005];
struct {
    ll weight,val;
} goods[1005];
ll t,n,c;
int main() {
    freopen("P2062.txt", "r", stdin);
    cin >> t;
    while (t--) {
        cin >> n >> c;
        memset(dp,0,sizeof(dp));
        for (int i = 1; i <= n; ++i) {
            cin >> goods[i].val;
        }
        for (int i = 1; i <= n; ++i) {
            cin >> goods[i].weight;
        } 
        for (int i = 1; i <= n; ++i)
            for (int j = c; j >= 0; --j) {
                if (goods[i].weight <= j) {
                    dp[j] = max(dp[j],dp[j-goods[i].weight]+goods[i].val);
                }
            }

        cout << dp[c] << '\n';
    }
}