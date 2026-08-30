//P1168 中位数
#include <bits/stdc++.h>
using namespace std;
#define ll long long
//const int MAXN = 2e6 + 5;
//int a[MAXN];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1168.txt","r",stdin);
    int n; cin >> n;
    priority_queue<ll,vector<ll>,less<ll>> gh;
    priority_queue<ll,vector<ll>,greater<ll>> mh;
    //小到大堆gh-mid-小到大堆mh
    ll mid=0;
    for (int i = 1; i <= (n+1)/2; ++i) {
        if (i == 1) {cin >> mid; cout << mid << '\n';continue;}
        ll tmp; cin >> tmp; if (tmp <= mid) gh.push(tmp); else mh.push(tmp);
        cin >> tmp; if (tmp <= mid) gh.push(tmp); else mh.push(tmp);
        if (gh.size() > mh.size()) {tmp = gh.top(); gh.pop(); mh.push(mid); mid = tmp;}
        else if (gh.size() < mh.size()) {tmp = mh.top(); mh.pop(); gh.push(mid); mid = tmp;}
        cout << mid << '\n';
    }
    return 0;
}
