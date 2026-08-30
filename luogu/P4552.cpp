//P4552 [Poetize6] IncDec Sequence
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 1e5 + 5;
ll d[MAXN];
ll a[MAXN];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P4552.txt","r",stdin);
    ll n; cin >> n;
    ll pos=0,neg=0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        d[i] = a[i] - a[i-1];
        if (i >= 2) {
            if (d[i] > 0) pos += d[i];
            else if (d[i] < 0) neg += (-d[i]);
        }
    }
    cout << max(pos,neg) << '\n';
    cout << (max(pos,neg) - min(pos,neg) + 1);


    return 0;
}
