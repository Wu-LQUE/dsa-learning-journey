//P1090 [NOIP 2004 提高组] 合并果子
#include <bits/stdc++.h>
using namespace std;
#define ll long long
//const int MAXN = 2e6 + 5;
//int a[MAXN];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1090.txt","r",stdin);
    int n; cin >> n;
    priority_queue<ll,vector<ll>,greater<ll>> mhp;
    for (int i = 0; i < n; ++i) {ll a; cin >> a; mhp.push(a); }
    ll ans=0; while(mhp.size()>1) {ll a=mhp.top();mhp.pop();ll b=mhp.top();mhp.pop();ans += a+b;mhp.push(a+b);}
    cout << ans;
    return 0;
}
