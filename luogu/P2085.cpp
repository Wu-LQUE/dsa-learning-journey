//P2085 最小函数值
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 1e4+5;
int a[MAXN];
int b[MAXN];
int c[MAXN];
int step[MAXN];
ll calc(ll f,ll x) {
    return (a[f]*x+b[f])*x+c[f];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P2085.txt","r",stdin);
    ll n,m; cin >> n >> m;
    priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> mhp;
    for (int i=1; i<=n; ++i) { cin >> a[i] >> b[i] >> c[i]; mhp.push({calc(i,1),i}); step[i] = 1;}
    for (int i = 1; i <= m; ++i) {
        auto cur = mhp.top();
        cout << cur.first << ' ';
        mhp.pop();
        mhp.push({calc(cur.second,++step[cur.second]),cur.second});
    }
    return 0;
}
