//P1824 [USACO05FEB] 进击的奶牛 Aggressive Cows G
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 2e5 + 5;
int n,m;
int a[MAXN];
ll check(ll dis) {
    ll cnt = 1,prev = 1;
    for (int i = 2; i <= n; ++i) {
        if (a[i] - a[prev] >= dis) {
            cnt++;
            prev = i;
            // i = prev;
        }
    }
    if (cnt >= m) return 1;
    else return 0;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1824.txt","r",stdin);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);
    ll l = 1,r=a[n]-a[1],mid;
    ll ans;
    while(l < r) {
        mid = (l + r) >> 1;
        if (check(mid)) {
            ans = mid;
            l = mid + 1;
        }else r = mid;
    }
    cout << ans;
    return 0;
}
