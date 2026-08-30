//P3948 数据结构
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 1e5 + 5;
ll ans[MAXN];
ll d[MAXN];
ll n,opt,mod,Min,Max;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P3948.txt","r",stdin);
    cin >> n >> opt >> mod >> Min >> Max;
    while (opt--) {
        ll L,R,X;
        char op; cin >> op >> L >> R;
        if (op == 'A') {
            cin >> X;
            d[L] += X;
            d[R+1] -= X;
        }else if (op == 'Q') {
            ll cnt = 0;
            for (int i = 1; i <= R; ++i) {
                ans[i] = ans[i-1] + d[i];
                if (i >= L) {
                    cnt += ((Min <= (ans[i]*i%mod)) && ((ans[i]*i%mod) <= Max));
                }
            }
            cout << cnt << '\n';
        }
    }
    ll f; cin >> f;
    for (int i = 1; i <= n; ++i) {
        d[i] += d[i-1];
        ans[i] = ans[i-1] + ((Min <= (d[i]*i%mod)) && ((d[i]*i%mod) <= Max));
    }
    while (f--) {
        ll l,r; cin >> l >> r;
        cout << ans[r] - ans[l-1] << '\n';
    }
    return 0;
}
