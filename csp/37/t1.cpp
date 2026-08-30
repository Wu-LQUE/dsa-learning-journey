#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e5+10;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t1.txt","r",stdin);
    ll b,c,l,r; cin >> b >> c >> l >> r;
    ll x = l + (l&1);
    ll tot = 0;
    for (;x <= r; x += 2) {
        tot += (x + b) * x + c;
    }
    cout << tot * 2 << endl;
}