//P1843 奶牛晒衣服
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 5e5;
int t[MAXN+5];
ll n,a,b;
bool fit(ll mid) {
    ll tot = mid;
    for (int i = 1; i <= n; ++i) {
        if (t[i] > a * mid) {
            ll rest = (t[i] - a * mid);
            tot -= (rest % b == 0 ? rest / b : rest / b + 1);
            if (tot < 0) return false;
        }
    }
    return true;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1843.txt","r",stdin);
    cin >> n >> a >> b;
    for (int i = 1; i <= n; ++i) cin >> t[i];
    ll l = 1,r = MAXN,mid;
    ll ans;
    while (l <= r) {
        mid = (l+r) >> 1;
        if (fit(mid)) {
            r = mid-1;
            ans = mid;
        }
        else l = mid + 1;
    }
    cout << ans << '\n';
    return 0;
}
