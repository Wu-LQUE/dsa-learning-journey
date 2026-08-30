//P1314 [NOIP 2011 提高组] 聪明的质监员
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 2e5 + 5;
ll w[MAXN];
ll v[MAXN];
ll n,m,s;
ll qzh1[MAXN],qzh2[MAXN];
pair<ll,ll> q[MAXN];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1314.txt","r",stdin);
    cin >> n >> m >> s;
    ll l=LLONG_MAX,r=LLONG_MIN;
    for (ll i = 1; i <= n; ++i) {
        cin >> w[i] >> v[i];
        l = min(l,w[i]);
        r = max(r,w[i]);
    }
    for (ll i = 1; i <= m; ++i) {
        cin >> q[i].first >> q[i].second;
    }
    ll best = LLONG_MAX,bestW;
    r+=1;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        for (ll i = 1; i <= n; ++i) {
            qzh1[i] = qzh1[i-1] + (w[i] >= mid);
            qzh2[i] = qzh2[i-1] + (w[i] >= mid) * v[i];
        }
        ll y = 0;
        for (ll i = 1; i <= m; ++i) {
            y += (qzh1[q[i].second]-qzh1[q[i].first-1]) * (qzh2[q[i].second]-qzh2[q[i].first-1]);
        }
        if (y < s) {
            r = mid - 1;
        } else if (y > s) {
            // l = mid;
            l = mid + 1;
        }
        if (llabs(s-y)<best) {
            best = abs(s-y);
            bestW = mid;
        }
        if (best == 0) break;
    }
    cout << best << '\n';
    return 0;
}
