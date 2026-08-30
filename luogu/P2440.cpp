//P2440 木材加工
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 1e5 + 5;
int a[MAXN];
ll n,k,sum=0;
bool fit(ll mid) {
    ll cnt = 0;
    for (int i = 1; i <= n; ++i) {
        cnt += a[i] / mid;
        if (cnt >= k) return true;
    }
    return false;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P2440.txt","r",stdin);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i]; sum += a[i];
    }
    ll l = 1,r = sum / k + 1;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        if (fit(mid)) l = mid + 1;
        else r = mid - 1;
    }
    cout << r << '\n';
    return 0;
}
