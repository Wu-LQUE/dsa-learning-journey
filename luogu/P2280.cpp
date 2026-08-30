//P2280 [HNOI2003] 激光炸弹
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 5e3+1;
int a[MAXN+10][MAXN+10];
ll n,m;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("P2280.txt","r",stdin);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        ll x,y,v; cin >> x >> y >> v;
        a[x+1][y+1] += v;
    }
    for (int i = 1; i <= MAXN; ++i) {
        for (int j = 1; j <= MAXN; ++j) {
            a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1]; 
        }
    }
    int maxv = -1;
    for (int i = 0; i <= MAXN - m ; ++i) {
        for (int j = 0; j <= MAXN - m ; ++j) {
            maxv = max(maxv,a[i+m][j+m] - a[i][j+m] - a[i+m][j] + a[i][j]);
        }
    }
    cout << maxv;
    return 0;
}
