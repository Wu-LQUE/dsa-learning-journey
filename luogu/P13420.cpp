//P13420 [COCI 2012/2013
#include <bits/stdc++.h>
#include <cstdio>
#include <ios>
using namespace std;
#define ll long long

const int MAXN = 1005;
ll a[MAXN];
int n;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P13420.txt", "r", stdin);
    cin >> n;
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            ll tmp; cin >> tmp; sum+=tmp;
            a[i] += tmp;
        }
    }
    ll aSum = sum / (2 * n - 2);
    if (n != 2) {
        for (int i = 0; i < n; ++i) {
            cout << (ll) (a[i] - aSum) / (n - 2) << ' ';
        }
    } else {
        cout << aSum/2 << ' ' << aSum/2;
    }
    
}
