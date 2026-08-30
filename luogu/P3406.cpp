//P3406 海底高铁
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 1e5 + 5;
typedef struct {
    ll A,B,C;
} node;
ll p[MAXN];
ll limit[MAXN]; //>=
node info[MAXN];
ll d[MAXN];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P3406.txt","r",stdin);
    ll n,m; cin >> n >> m;
    for (int i = 1; i <= m; i++) cin >> p[i];
    for (int i = 1; i < n; i++) {
        cin >> info[i].A >> info[i].B >> info[i].C;
        limit[i] = info[i].C/(info[i].A-info[i].B) + 1;
    }
    ll s,t;
    for (int i = 1; i <= m-1; ++i) {
        s = min(p[i],p[i+1]);
        t = max(p[i],p[i+1]);
        d[s] += 1;
        d[t] -= 1;
    }
    for (int i = 1; i < n; i++) d[i]+=d[i-1];
    ll tot=0;
    for (int i = 1; i < n; ++i) {
        if (d[i] >= limit[i]) tot += (info[i].C +info[i].B*d[i]);
        else tot += info[i].A * d[i];
    }
    cout << tot;
    return 0;
}
