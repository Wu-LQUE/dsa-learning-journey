//P2240 【深基12.例1】部分背包问题
#include <bits/stdc++.h>
using namespace std;
#define ll long long
//const int MAXN = 2e6 + 5;
struct coin {
    ll m,v;
    double p;
};
coin a[100+5];
ll n,t;
const double ZERO = 1e-6;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P2240.txt","r",stdin);
    cin >> n >> t;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].m >> a[i].v;
        a[i].p = (double) a[i].v / a[i].m;
    }
    sort (a+1,a+n+1,[](const coin &c1,const coin &c2){
        return c1.p > c2.p;
    });
    double ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (t >= a[i].m) {
            ans += a[i].v;
            t -= a[i].m;
        } else {
            ans += a[i].p * t;
            break;
        }
    }
    cout << fixed << setprecision(2) << ans << '\n';
    return 0;
}
