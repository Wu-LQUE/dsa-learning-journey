//P2249 【深基13.例1】查找
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 10e6 + 5;
int a[MAXN];
ll n,m;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P2249.txt","r",stdin);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    while (m--) {
        ll target; cin >> target;
        auto idx = lower_bound(a+1,a+n+1,target);
        if (idx == a+n+1 || *idx != target) cout << -1 << ' ';
        else cout << idx - a << ' ';
    }
    return 0;
}
