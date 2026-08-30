//P4995 跳跳！
#include <bits/stdc++.h>
using namespace std;
#define ll long long
//const int MAXN = 2e6 + 5;
int a[400],visited[400];
int n;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P4995.txt","r",stdin);
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    ll tot = 0;
    int pos = 0;
    for (int i = 1; i <= n; ++i) {
        ll maxStep = LLONG_MIN;int next = -1;
        for (int j = 1; j <= n; ++j) {
            if (!visited[j]) {
                if ((a[j]-a[pos])*(a[j]-a[pos])>maxStep) {
                    maxStep = (a[j]-a[pos])*(a[j]-a[pos]);
                    next = j;
                }
            }
        }
        visited[next] = 1;
        tot += maxStep;
        pos = next;
    }
    cout << tot << '\n';
    return 0;
}
