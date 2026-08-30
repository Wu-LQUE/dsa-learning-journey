#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 605;
// ll d[N][N];
ll a[N][N];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t2.txt","r",stdin);
    ll n,L,r,t; cin >> n >> L >> r >> t;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            a[i][j] = a[i][j] + a[i-1][j] + a[i][j-1] - a[i-1][j-1];
        }
    }
    ll tot = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            ll x1 = max(i-r,(ll)1), x2 = min(i+r,n);
            ll y1 = max(j-r,(ll)1), y2 = min(j+r,n);
            ll area = a[x2][y2] - a[x1-1][y2] - a[x2][y1-1] + a[x1-1][y1-1];
            ll cnt = (x2-x1+1)*(y2-y1+1);
            if (area <= cnt * t) tot++;
        }
    }
    cout << tot;
}