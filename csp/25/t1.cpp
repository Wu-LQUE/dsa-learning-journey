#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t1.txt","r",stdin);
    set<ll> a;
    ll n,k; cin >> n >> k;
    ll cnt = 0;
    for (int i = 1; i <= k; ++i) {
        ll x,y; cin >> x >> y;
        if (y!=0&&!a.count(y)) cnt++;
        a.insert(x);
    }
    cout << cnt << endl;
}