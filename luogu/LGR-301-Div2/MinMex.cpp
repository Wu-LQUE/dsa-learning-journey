#include <algorithm>
#include <bits/stdc++.h>
#include <cmath>
#include <functional>
#include <ios>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
#define ll long long
ll t,n,k;
const ll maxn = 2*10e5+5;
ll a[maxn];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("ta.txt","r",stdin);
    cin >> t;
    while (t--) {
        cin >> n >> k;
        if (k <= 0) {cout << "-1\n"; continue;}
        for (ll i = 1; i <=n; ++i) cin >> a[i];
        sort(a+1,a+n+1,less<ll>());
        if (k==1) {
            cout << ((a[1]==1) ? "-1\n" : "0\n");
            continue;
            // cout << (lower_bound(a+1,a+n+1,k) <= a + n) ?  
        }
        ll need = 1;
        ll i = 1;
        ll tot = 0;
        while (need <= k-1 && i <= n) {
            if (a[i] < need) i++;
            else if(a[i] == need) {need++;i++;}
            else if (a[i] > need) {tot+=a[i]-need;need++;i++;}
            else break; 
        }
        
        if (need >= k) {
            cout << tot + (upper_bound(a+i,a+n+1,k)-lower_bound(a+i,a+n+1,k)) << '\n';
        }else {
            cout << "-1\n";
        }
    }
    //     if (k <= 0) {
    //         cout << "-1\n"; continue; 
    //     }
    //     priority_queue<ll,vector<ll>,greater<ll>> gk;
    //     priority_queue<ll,vector<ll>,greater<ll>> lk;
    //     ll kNum = 0;
    //     ll tot = 0;
    //     for (ll i = 1; i <= n; ++i) {
    //         ll tmp; cin >> tmp;
    //         if (tmp == k) {
    //             kNum++;
    //         }else if (tmp > k) {
    //             gk.push(tmp);
    //         }else {
    //             lk.push(tmp);
    //         }
    //     }
    //     if (k==1) {
    //         if (kNum==0) cout << "0\n";
    //         else cout << "-1\n";
    //         continue;
    //     }
    //     ll need = 1;
    //     while (need <= k-1) {
    //         if (!lk.empty()) {
    //             while (!lk.empty() && lk.top()<need) {
    //                 lk.pop();
    //             }
    //             if (lk.empty()) continue;
    //             if (lk.top()==need) {
    //                 lk.pop();need++;continue;
    //             }else {
    //                 tot+=lk.top()-need;need++;lk.pop();continue;
    //             }
    //         }else if (kNum > 0) {
    //             tot += k-need;need++;kNum--;continue;
    //         }else if (!gk.empty()) {
    //             tot += gk.top()-need;need++;gk.pop();continue;
    //         }else {
    //             break;
    //         }
    //     }
        
    //     if (need >= k) cout << tot+kNum << '\n';
    //     else cout << "-1\n";
    // }
}