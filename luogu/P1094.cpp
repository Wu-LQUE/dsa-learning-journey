//P1094 [NOIP 2007 普及组] 纪念品分组
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 3*10e4 + 5;
int a[MAXN];
int w,n;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1094.txt","r",stdin);
    cin >> w >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    sort(a+1,a+n+1,less<int>());
    int ans = 0,l = 1,r = n;
    while (l <= r) {
        if (a[l]+a[r]<=w) {
            l++,r--;
            ans++;
        } else {
            r--;
            ans++;
        }
    }
    cout << ans << '\n';
    return 0;
}
