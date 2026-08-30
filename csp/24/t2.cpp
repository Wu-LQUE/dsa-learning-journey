#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 1e5+10;
ll a[MAXN];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t2.txt","r",stdin);
    ll n,N; cin >> n >> N;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    ll r = N/(n+1);
    a[n+1] = N;
    ll cnt = 0;
    //遍历f的值,对应a[f]~a[f+1]-1
    for (int f = 0; f <= n; ++f) {
        ll j = a[f],g;
        while (j <= a[f+1]-1) {
            g = j/r;
            ll right = g * r + r - 1;
            right = min(a[f+1]-1,right);
            cnt += abs(f-g) * (right - j + 1);
            j += right - j + 1;
        }
    }
    cout << cnt << endl;
}