#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5*10e3+5;
int n,m;
struct villager{
    int p,a;
};
villager v[N];
int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    freopen("P1208.txt","r",stdin);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> v[i].p >> v[i].a;
    }
    sort(v+1,v+m+1,[](const villager& v1,const villager& v2){
        return v1.p < v2.p;
    });
    ll tot = 0,i = 1;
    while (n > 0) {
        if (v[i].a <= n) {
            tot += v[i].p * v[i].a;
            n -= v[i].a;
        }else {
            tot += v[i].p * n;
            n -= n;
        }
        i++;
    }
    cout << tot << '\n';
}