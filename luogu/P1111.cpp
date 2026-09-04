//P1111 修复公路
#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#define ll long long
//const int MAXN = 2e6 + 5;
//int a[MAXN];
int fa[1000+5];
struct road{
    int x,y,t;
}rd[100000+5];
inline bool cmp(const road &a,const road &b) {
    return a.t < b.t;
}
int n,m;
int find_set(int x) {
    if (fa[x] == x) return x;
    return fa[x] = find_set(fa[x]);
}
void hb(int x, int y) {
    int fx = find_set(x),fy = find_set(y);
    fa[fx] = fy;
}
//判断独立集合个数
bool check() {
    int sum = 0;
    for (int i = 1; i<=n; ++i) {
        if (fa[i]==i) sum++;
        if (sum==2) return 0;
    }
    return 1;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1111.txt","r",stdin);
    cin >> n >> m;
    if (m < n-1) {cout << -1;return 0;}
    for (int i = 1; i <= m; ++i) {
        cin >> rd[i].x >> rd[i].y >> rd[i].t;
    }
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
    }
    sort(rd+1,rd+m+1,cmp);
    for (int i = 1; i <= m; ++i) {
        hb(rd[i].x,rd[i].y);
        if (check()) {cout << rd[i].t;return 0;}
    }
    cout << -1;
    // ll l=1,r=rd[m].t+1,ans=-1;
    // while (l < r) {
    //     ll mid = (l + r) >> 1;
    //     if (check(mid)) {
    //         ans = mid;
    //         r = mid-1;
    //     }else l = mid+1;
    // }
    // if (ans!=-1) cout << ans;
    return 0;
}
