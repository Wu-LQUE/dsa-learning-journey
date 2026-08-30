//P3378 【模板】堆
#include <bits/stdc++.h>
using namespace std;
#define ll long long
//const int MAXN = 2e6 + 5;
//int a[MAXN];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P3378.txt","r",stdin);
    priority_queue<ll,vector<ll>,greater<ll>> minHeap;
    int m; cin >> m;
    for (int i = 1; i <= m; ++i) {
        ll op; ll num;
        cin >> op;
        if (op == 1) {
            cin >> num; minHeap.push(num);
        }else if (op == 2) {
            cout << minHeap.top() << '\n';
        }else if (op == 3) {
            minHeap.pop();
        }
    }
    return 0;
}
