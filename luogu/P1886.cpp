#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 1e6 + 5;
int a[MAXN];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1886.txt","r",stdin);
    int n,k; cin >> n >> k;
    for (int i = 1; i <=n; ++i) cin >> a[i];
    deque<int> q;
    //构造最小值队列
    for (int i = 1; i <= n; ++i) {
        while (q.size() > 0 && a[q.back()] > a[i]) q.pop_back();
        q.push_back(i);
        if (i >= k) {
            if (q.size() > 0 && q.front()<= i-k) q.pop_front(); 
            cout << a[q.front()] << " ";
        }
    }
    cout << '\n'; 
    q.clear();
    //构造最大值队列
    for (int i = 1; i <= n; ++i) {
        while (q.size() > 0 && a[q.back()] < a[i]) q.pop_back();
        q.push_back(i);
        if (i >= k) {
            if (q.size() > 0 && q.front()<= i-k) q.pop_front(); 
            cout << a[q.front()] << " ";
        }
    }
}