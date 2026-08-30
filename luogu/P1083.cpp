//P1083 [NOIP 2012 提高组] 借教室
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 1e6 + 5;
ll r[MAXN];
typedef struct Anode {
    ll d,s,t;
} node;
node a[MAXN];
ll d[MAXN];
ll n,m;
bool check(ll mid) {
    for (int i = 1; i <= n; ++i) {
        d[i] = r[i] - r[i-1];
    }
    for (int i = 1; i <= mid; ++i) {
        ll num=a[i].d,s=a[i].s,t=a[i].t;
        d[s] += -num;
        d[t+1] -= -num;
    }
    for (int i = 1; i <= n; ++i) {
        d[i] += d[i-1];
        if (d[i] < 0) return false;
    }
    return true;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1083.txt","r",stdin);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> r[i];
    for (int i = 1; i <= m; ++i) cin >> a[i].d >> a[i].s >> a[i].t;
    ll l = 1,r = m,mid;
    while (l < r) {
        mid = (l + r) >> 1;
        if (check(mid)) {
            l = mid + 1;
        }else {
            r = mid;
        }
    }
    if (l >= m) cout << 0;
    else {
        cout << -1 << '\n';
        cout << l;
    }
    return 0;
}
