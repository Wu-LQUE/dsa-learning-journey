#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n;
int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cin >> n;
    ll sum = 0;
    while (n--) {
        ll w,x; cin >> w >> x;
        sum += w*x;
    }
    cout << (sum >= 0 ? sum : 0) << '\n';

}