#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e5 + 10;
ll a[N],b[N],c[N];
ll mL[N],mR[N];
ll n;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t2.txt","r",stdin);
    cin >> n;
    for (int i = 0; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    ll tot = 0,Max = LLONG_MIN;
    for (int i = 0; i <= n; ++i) {
        tot += a[i] - b[i];
        if (tot > Max) Max = tot;
        mL[i] = Max;
        c[i] = tot;
    }
    Max = LLONG_MIN;
    for (int i = n; i >= 0; --i) {
        if (c[i] > Max) Max = c[i];
        mR[i] = Max;
    }
    for (int i = 1; i <= n; ++i) cout << max(mL[i-1],mR[i]+b[i]) << ' ';
}