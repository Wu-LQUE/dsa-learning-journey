//P13787 地毯 加强版
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 5000 + 5;
int a[MAXN][MAXN];
ll n,m;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P13787.txt","r",stdin);
    cin >> n >> m;
    while (m--) {
        ll x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
        a[x1][y1] += 1;
        a[x1][y2+1] -= 1;
        a[x2+1][y1] -= 1;
        a[x2+1][y2+1] += 1;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) 
            a[i][j] = a[i-1][j] + a[i][j-1] + a[i][j] - a[i-1][j-1];
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            ans += (i + j) ^ a[i][j];
    cout << ans <<'\n';
    return 0;
}
