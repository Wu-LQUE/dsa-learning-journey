#include <bits/stdc++.h>
#define ll long long
// const int N = ;
using namespace std;
ll dp[(int)3e5+1];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t2.txt","r",stdin);
    ll n,x,total=0; cin >> n >> x;
    ll a[31]; for (int i = 1; i <= n; ++i) {cin >> a[i];total+=a[i];}
    for (int j = 0; j <= total; ++j) {
        dp[j] = total;
    }
    for (int i = 1; i <= n; ++i) 
        for (int j = total; j >= 1; --j) {
            if (j - a[i] < x) {dp[j] = dp[j]; continue;}
            else dp[j] = min(dp[j],dp[j-a[i]]-a[i]);
        }
    ll minw = LLONG_MAX;
    for (int i = 1; i <= total; ++i) {
        if (dp[i] < minw) minw = dp[i];
    }
    cout << minw;
}