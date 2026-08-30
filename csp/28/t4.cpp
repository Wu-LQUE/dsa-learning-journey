#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct tree {
    vector<tree*> children;
    ll a;
    ll p;
    tree() : a(0),p(0){}
};

ll bfs(tree *root) {
    queue<tree*> q;
    q.push(root);
    // ll minAbs = 0;
    multiset<ll> s;
    while (q.size()) {
        tree *t = q.front(); q.pop();
        s.insert(t->a);
        for (auto child : t->children) q.push(child);
    }
    ll minAbs = 0;
    ll total = 0;
    for (auto it = s.begin(); it != s.end(); ++it) {
        auto pre = prev(it);
        auto nxt = next(it);
        if (s.size()<=1) minAbs = 0;
        else if (it == s.begin()) minAbs = abs(*nxt - *it);
        else if (it == s.end()) minAbs = abs(*it - *pre);
        else minAbs = min(abs(*nxt - *it),abs(*it - *pre));
        total += minAbs * minAbs;
    }
    return total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t4.txt","r",stdin);
    ll n; cin >> n;
    vector<tree*> arr(n+1);
    for (ll i = 1; i <= n; ++i) arr[i]=new tree();
    for (ll i = 2; i <= n; ++i) {ll p; cin >> p; arr[i]->p = p; arr[p]->children.push_back(arr[i]); } 
    for (ll i = 1; i <= n; ++i) cin >> arr[i]->a;
    //暴力穷举
    for (ll i = 1; i <= n; ++i) {
        ll total = bfs(arr[i]);
        cout << total << endl;
    }
}