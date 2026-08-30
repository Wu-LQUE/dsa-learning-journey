//P1102 A-B 数对
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 2e5 + 5;
int a[MAXN];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1102.txt","r",stdin);
    int n,c; cin >> n >> c;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1,a + n + 1);
    ll ans = 0;
    for (int i=1,j=1,k=1; i <= n; ++i) {
        while (j <= n && a[j] - a[i] < c) j++;
        while (k <= n && a[k] - a[i] <= c) k++;
        if (a[j] - a[i] == c && a[k-1] - a[i] == c && k-1>=1) ans += k-j;
    }
    cout << ans;
    return 0;
}
