#include <bits/stdc++.h>
using namespace std;
#define ll long long
// const int N = 1e5+10;
ll a[205];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t1.txt","r",stdin);
    ll n,N; cin >> n >> N;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    a[n+1] = N;
    ll cnt = 0;
    for (int i = 0; i <= n; ++i) {
        cnt += i * (a[i+1]-a[i]);
    }
    cout << cnt << endl;
}