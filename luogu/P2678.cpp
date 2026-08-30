//P2678 [NOIP 2015 提高组] 跳石头
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 50005;
int a[MAXN];
int l,n,m;
bool check(ll dis) {
    ll cnt = 0,curdis = 0;
    for (ll j = 1; j <= n+1; ++j) {
        curdis += a[j];
        if (curdis >= dis) {
            curdis = 0;
        }else {
            cnt++;
        }
    }
    if (cnt > m ) return false;
    else return true;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P2678.txt","r",stdin);
    cin >> l >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    a[0] = 0; a[n+1] = l+1;
    for (int i = n+1; i >= 1; --i) a[i] -= a[i-1];
    ll left = 1,right = l+1;
    while (left < right) {
        ll mid = (left + right) >> 1;
        if (check(mid)) {  
            left = mid+1;
        }else {
            right = mid;
        }
    }
    cout << left - 1;
    return 0;
}
