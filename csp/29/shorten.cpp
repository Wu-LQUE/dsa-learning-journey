#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long

bool cmp(const pair<ll,ll> &a,const pair<ll,ll> &b) {
    return a.first < b.first;//第一个键小的排前面
}
int binarySearchFirst(const vector<pair<ll,ll>>& tc, ll target) {
    int left = 0, right = tc.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (tc[mid].first == target) {
            result = mid;  // 找到，但继续向左找第一个出现的
            right = mid - 1;  // 向左继续查找
        } 
        else if (tc[mid].first < target) {
            left = mid + 1;
        } 
        else {
            right = mid - 1;
        }
    }
    
    return result;  // 返回第一个出现的位置，没找到返回-1
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("shorten.txt","r",stdin);
    ll n,m,k; cin >> n >> m >> k;
    vector<pair<ll,ll>> tc(n);
    for (int i = 0; i < n; ++i) {
        ll t,c; cin >> t >> c;
        tc[i] = make_pair(t,c);
    }
    sort(tc.begin(),tc.end(),cmp);
    vector<ll> price(n);
    for (int i = 0; i < n; ++i) {
        if (i == 0) price[i] = tc[i].second;
        else price[i] = price[i-1] + tc[i].second;
    }
    cout << "fuck??" << endl;
    ll right = n-1;
    ll left = binarySearchFirst(tc,tc[right].first)-1;
    while (m > 0) {
        ll cost;
        if (left < 0) cost = price[right];
        else cost = (price[right] - price[left]);
        if (m < cost) break;
        while (m >= cost) {
            m -= cost;
            tc[right].first--;
            if (left >= 0 && tc[right].first == tc[left].first) {
                left = binarySearchFirst(tc,tc[right].first)-1;
                break;
            }
        }
    }
    cout << max(tc[right].first,k) << endl;
}