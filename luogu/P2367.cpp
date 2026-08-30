//P2367 语文成绩
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 5*10e6 + 5;
int a[MAXN];
ll n,p;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P2367.txt","r",stdin);
    cin >> n >> p;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = n; i >= 1; --i) a[i] -= a[i-1];
    while (p--) {
        ll x,y,z; cin >> x >> y >> z;
        a[x] += z; a[y+1] -= z;
    }
    for (int i = 1; i <= n; ++i) a[i] += a[i-1];
    sort(a+1,a+1+n,less<int>());
    cout << a[1] << '\n';
    return 0;
}
