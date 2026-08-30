#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 10e5+5;
ll zeros[N],ones[N];
struct example{
    ll num,res;
};
example e[N];
ll m;
int main() {
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> e[i].num >> e[i].res;
    }
    sort(e+1,e+1+m,[](const example &e1,const example &e2){
        return e1.num < e2.num;
    });
    for (int i = 1; i <= m; ++i) {
        ll tmp = e[i].res;
        zeros[i] = zeros[i-1] + (tmp == 0);
        ones[i] = ones[i-1] + (tmp == 1);
    }
    ll best = LLONG_MIN,bestI = -1;
    for (int i = 1; i <= m; ++i) {
        ll cnt = zeros[i-1] + ones[m] - ones[i-1];
        if (cnt >= best) {
            best = cnt;
            bestI = i;
        }
    }
    cout << e[bestI].num << '\n';
}