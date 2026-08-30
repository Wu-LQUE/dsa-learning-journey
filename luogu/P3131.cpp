//P3131 [USACO16JAN] Subsequences Summing to Sevens S
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 5e4 + 5;
ll a[MAXN];
ll n;
ll best1[7];
ll best2[7];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P3131.txt","r",stdin);
    cin >> n;
    memset(best1,-1,sizeof best1);
    memset(best2,-1,sizeof best2);
    best1[0] = best2[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i] += a[i-1];
        a[i] %= 7;
        if (best1[a[i]]==-1) {
            best1[a[i]] = i;
            best2[a[i]] = i;
        }
        if (best2[a[i]] < i) best2[a[i]] = i;
    }
    ll maxL = -1;
    for (int i = 0; i < 7; ++i) {
        ll len = best2[i] - best1[i];
        maxL = max(maxL,len);
    }
    cout << maxL;
    return 0;
}
