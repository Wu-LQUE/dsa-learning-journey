#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e5 + 10;
ll a[N];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t1.txt","r",stdin);
    ll Max = 0,MinTot = 0,Min = 0,n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        Max += a[i];
        Min = min(Min,a[i]);
        if (a[i] > a[i-1]) MinTot += a[i];
        else MinTot += Min;
    }
    cout << Max << endl << MinTot << endl; 
}