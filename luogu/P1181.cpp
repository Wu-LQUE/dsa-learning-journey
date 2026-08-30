//P1181 数列分段 Section I
#include <bits/stdc++.h>
using namespace std;
#define ll long long
//const int MAXN = 2e6 + 5;
//int a[MAXN];
int n,m;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1181.txt","r",stdin);
    cin >> n >> m;
    ll ans = 0,tot = 0;
    for (int i = 1; i <= n; ++i) {
        ll tmp; cin >> tmp;
        if (tot + tmp > m) {
            tot = tmp; ans++;
        }else {
            tot += tmp;
        }
    }
    ans++;
    cout << ans << '\n';
    return 0;
}
