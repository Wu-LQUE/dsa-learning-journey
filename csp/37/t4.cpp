#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e6+10;
const ll mod = 998244353;
ll a[N],n;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t4.txt","r",stdin);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    ll tot = 0;
    for (int i = 1; i <= n; ++i) {
        ll tmp = a[i];
        for (int j = i; j <= n; ++j) {
            if (j == i) {
                tot += i * j * a[i];
            }
            else {
                if (tmp == 1) {
                    tot += i * j;
                }else {
                    tmp = gcd(tmp,a[j]);
                    tot += i * j * tmp;
                }
            }
            tot %= mod;
        }
    }
    cout << tot << endl;
}