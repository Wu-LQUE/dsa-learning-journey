//P5091 【模板】扩展欧拉定理
#include <bits/stdc++.h>
using namespace std;
#define ll long long
//const int MAXN = 2e6 + 5;
//int a[MAXN];
ll a,m; string b_str;
ll qpow(ll a,ll n,ll m) {
    ll res = 1;
    a %= m;
    while (n) {
        if (n & 1) res = (res * a) % m;
        a = (a * a) % m;
        n >>= 1;
    }
    return res;
}
ll phi(ll x) {
    ll res = x;
    for (ll i = 2; i * i <= x; ++i) {
        if (!(x%i)) {
            res = res / i * (i-1);
            while (!(x%i)) x /= i;
        }
    }
    if (x > 1) res = res / x * (x-1);
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P5091.txt","r",stdin);
    cin >> a >> m >> b_str;
    ll phim = phi(m);
    ll b_mod = 0;
    bool flag = false;
    for (char ch : b_str) {
        b_mod = b_mod * 10 + (ch - '0');
        if (b_mod >= phim) {
            flag = true;
            b_mod %= phim;
        }
    }
    if (flag) b_mod += phim;
    cout << qpow(a,b_mod,m) << '\n';
    return 0;
}
