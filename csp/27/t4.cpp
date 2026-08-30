#include <bits/stdc++.h>
#define ll long long
const int N = 2*(10e5)+10;
ll a[N];
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t4.txt","r",stdin);
    ll n,m,q; cin >> n >> m >> q;
    map<ll,ll> res;
    while (q--) {
        ll op; cin >> op;
        if (op == 1) {
            ll l,r,x; cin >> l >> r >> x;
            for (int i = l; i <= r; ++i) a[i] = x;
        }else if (op == 2) {
            ll x,w; cin >> x >> w;
            for (int i = 1; i <= n; ++i) {
                if (a[i] == x) a[i] = w;
            }
        }else if (op == 3) {
            ll x,y; cin >> x >> y;
            for (int i = 1; i <= n; ++i) {
                if (a[i] == x) a[i] = y;
                else if (a[i] == y) a[i] = x;
            }
        }else if (op == 4) {
            ll cnt=0,w; cin >> w;
            for (int i = 1; i <= n; ++i) {
                if (a[i] == w) cnt++;
            }
            cout << cnt << '\n';
        }else if (op == 5) {
            res.clear();
            for (int i = 1; i <= n; ++i) {
                if (a[i] != 0) {
                    res[a[i]]++;
                }
            }
            
            ll maxM = 0, maxCnt = 0;
            for (auto t : res) {
                if (t.second > maxCnt) {
                    maxM = t.first;
                    maxCnt = t.second;
                }
            }
            cout << maxM << '\n'; 
        }
    }
}