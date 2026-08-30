#include <bits/stdc++.h>
#define ll long long
const int N = 1010;
using namespace std;
// ll dp[(int)3e5+1];
struct node {
    ll d,u,r;
};
set<ll> risk[N],res; //风险日期
vector<struct node> day[N]; //每日数据
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t3.txt","r",stdin);
    ll n; cin >> n;
    for (int i = 0; i < n; ++i) {
        ll r,m; cin >> r >> m;
        while (r--) {
            ll riskday; cin >> riskday;
            for (int j = i; j <= i + 6; ++j) risk[j].insert(riskday);
        }
        while (m--) {
            ll D,U,R; cin >> D >> U >> R;
            if (D < 0) continue;
            if (!risk[D].count(R)) continue;
            day[i].push_back({D,U,R});
        }
        //检查前6天到今天的数据
        for (int j = max(0,i-6); j <= i; ++j) {
            for (auto t : day[j]) {
                ll d,u,r;
                d = t.d; u=t.u; r=t.r;
                bool flag =true;
                if (d < i - 6) continue;
                for (int k = d; k <= i && flag == true; ++k) 
                    if (!risk[k].count(r)) flag = false;
                if (!flag) continue;
                res.insert(u);
            }
        }
        cout << i << ' ';
        for (auto user : res) cout << user << ' ';
        cout << '\n';
        res.clear();
    }
}