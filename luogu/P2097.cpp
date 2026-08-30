//P2097 资料分发 1
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 1e5 + 5;
vector<int> adj[MAXN];
bool visited[MAXN];
ll n,m;
void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P2097.txt","r",stdin);
    cin >> n >> m;
    if (n==0) {
        cout << 0; return 0;
    }
    for (int i = 1; i <= m; ++i) {
        ll p,q; cin >> p >> q;
        adj[p].push_back(q);
        adj[q].push_back(p);
    }
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            ans++;
            dfs(i);
        }
    }
    cout << ans;
    return 0;
}
