#include <bits/stdc++.h>
#define ll long long
const int N = 1e5+10;
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t1.txt","r",stdin);
    ll a[30];
    ll b[30];
    ll n,m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    // a[0] = 1;
    ll c = 1;//c0=1
    ll last = 0;
    for (int i = 1; i <= n; ++i) {
        ll cnxt = c*a[i];
        ll cur = m % cnxt;
        b[i] = (cur - last) / c;
        last = cur;
        c = cnxt;
    }
    for (int i = 1; i <= n; ++i) cout << b[i] << ' ';
}