#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;
const int N = 1000+10;
ll d[N][N];
ll n,m;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    while (m--) {
        ll x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
        d[x1][y1] += 1;
        d[x1][y2+1] -= 1;
        d[x2+1][y1] -= 1;
        d[x2+1][y2+1] += 1;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            d[i][j] += d[i-1][j] + d[i][j-1] - d[i-1][j-1];
            cout << d[i][j] << ' ';
        }
        cout << '\n';
    }
    
}