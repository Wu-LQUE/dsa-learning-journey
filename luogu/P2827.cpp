//P2827 [NOIP 2016 提高组] 蚯蚓
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 1e5 + 5;
int tmp[MAXN];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P2827.txt","r",stdin);
    ll n,m,q,u,v,t; cin >> n >> m >> q >> u >> v >> t;
    // double p = (double)u/v;
    queue<ll> a,b,c; for (int i = 0; i < n; ++i) { cin >> tmp[i];}
    sort(tmp,tmp+n); for (int i = n-1; i >= 0; --i) { a.push(tmp[i]);}
    for (int i = 1; i <= m; ++i) {
        ll maxn = LLONG_MIN; ll f = -1;
        if (!a.empty() && a.front() > maxn)  {maxn = a.front();f=1;}
        if (!b.empty() && b.front() > maxn)  {maxn = b.front();f=2;}
        if (!c.empty() && c.front() > maxn)  {maxn = c.front();f=3;}
        maxn += (i-1)*q; ll x = maxn * u / v; ll y = maxn - x;
        if (f == 1) a.pop(); else if (f == 2) b.pop(); else c.pop();
        b.push(x-i*q); c.push(y - i*q);
        if (!(i % t)) cout << maxn << ' '; 
    }
    cout << endl;
    for (int i = 1; i <= n+m; i++) {
        ll maxn = LLONG_MIN; ll f = -1;
        if (!a.empty() && a.front() > maxn)  {maxn = a.front();f=1;}
        if (!b.empty() && b.front() > maxn)  {maxn = b.front();f=2;}
        if (!c.empty() && c.front() > maxn)  {maxn = c.front();f=3;}
        if (f == 1) a.pop(); else if (f == 2) b.pop(); else c.pop();
        if (!(i % t)) cout << maxn + m*q << ' ';
    }
    return 0;
}
