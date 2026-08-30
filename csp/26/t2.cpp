#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1005;
ll n,l,s;
ll x[N],y[N],b[N][N];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t2.txt","r",stdin);
    cin >> n >> l >> s;
    for (int i = 1; i <= n; ++i) cin >> x[i] >> y[i];
    ll one = 0;
    for (int i = 0; i <= s; ++i)
        for (int j = 0; j <= s; ++j) {cin >> b[s-i][j]; one += b[s-i][j];}
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (x[i] > l - s || y[i] > l - s) continue;
        ll cnt = 0;
        for (int j = 1; j <= n; ++j) {
            if (cnt == -1) continue;
            if (x[j] >= x[i] && x[j] <= x[i] + s && y[j] >= y[i] && y[j] <= y[i] + s) {
                if (b[x[j]-x[i]][y[j]-y[i]]==1) {
                    cnt++;
                }else {
                    cnt=-1;
                }
            }
        }
        ans += (cnt == one);
    }
    cout << ans << endl;
}