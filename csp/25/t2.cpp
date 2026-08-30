#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 2e5+10;
ll n,m,k;
ll d[N];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t2.txt","r",stdin);
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
        ll t,c; cin >> t >> c;
        ll l = t - (c-1) - k, r = t - k;
        l = max((ll)0,l); r = max((ll)0,r);
        d[l]++; d[r+1]--;
    }
    for (int i = 1; i <= N; ++i) {
        d[i] += d[i-1];
    }
    while (m--) {
        ll q; cin >> q;
        cout << d[q] << '\n';
    }
}