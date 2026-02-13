#include <bits/stdc++.h>
using namespace std;
#define ll long long

// 从0开始编号
ll ysf(ll n,ll m,ll k) {
    ll out;
    if (k == 1) {
        out = (m-1)%n;
    }else {
        out = (ysf(n-1,m,k-1) + m)%n;
    }
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("约瑟夫.txt","r",stdin);
    ll n,m; cin >> n >> m;
    // for (ll i = 1; i <= n; ++i) {
    //     cout << ysf(n,m,i) + 1 << " ";
    // }
    //双向链表list解法
    list<int> node;
    for (ll i = 1; i <= n; ++i) node.push_back(i);
    auto it = node.begin();
    while (node.size()>1) {
        for (int i = 1; i < m; ++i) {
            it++;
            if (it == node.end()) it = node.begin();
        }
        cout << *it << " ";
        auto next = ++it;
        if (next == node.end()) next = node.begin();
        node.erase(--it);
        it = next;
    }
    cout << *it;
}