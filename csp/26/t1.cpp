#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e5+10;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t1.txt","r",stdin);
    vector<ll> a;
    ll n; cin >> n; a.reserve(n+1);
    ll tot=0;
    for (int i = 1; i <= n; ++i){
        cin >> a[i]; tot += a[i];
    }
    double average = (double) tot / n;
    double D = 0;
    for (int i = 1; i <= n; ++i){
        D+=(a[i]-average)*(a[i]-average);
    }
    D/=n;
    D = sqrtl(D);
    for (int i = 1; i <= n; ++i){
        double res = (a[i] - average)/D;
        cout << setprecision(16) << res << '\n';
    }
}