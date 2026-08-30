#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t1.txt","r",stdin);
    ll n; cin >> n; double i; cin >> i; 
    double total = 0;
    double ii = 1;
    for (int j = 0; j <= n; ++j) {
        double t; cin >> t;
        total += t/ii;
        ii *= (1+i);
    }
    cout << total << endl;
}