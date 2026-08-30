//P1440 求m区间内的最小值
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 2e6 + 5;
int a[MAXN];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1440.txt","r",stdin);
    int n,m; cin >> n >> m;
    deque<int> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        if (i == 1) {
            cout << 0 << ' ';
        }else {
            while(!q.empty() && a[q.back()] > a[i-1]) q.pop_back();
            q.push_back(i-1);
            if (!q.empty() && q.front() <= i-1 - m) q.pop_front();
            cout << a[q.front()] << ' ';
        }
    }
}