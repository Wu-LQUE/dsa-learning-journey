//P1106 删数问题
#include <bits/stdc++.h>
using namespace std;
#define ll long long
//const int MAXN = 2e6 + 5;
//int a[MAXN];
string a,st;
ll n,k;
// priority_queue<int> bigq;
// priority_queue<int,vector<int>,less<int>> bigq2;
// priority_queue<int,vector<int>,greater<int>> lessq1;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1106.txt","r",stdin);
    cin >> a >> k; n = a.length();

    // ll newLen = n - k;
    // ll l = 0,r = k;
    // for (int i = 0; i < newLen; ++i) {
    //     ll best = LLONG_MAX; ll bestI = -1;
    //     for (int j = l; j <= r; ++j) {
    //         if (a[j]<best) {
    //             best = a[j];
    //             bestI = j;
    //         }
    //     }
    //     b.push_back(a[bestI]);
    //     l = bestI + 1; r++;
    // }
    // cout << stoull(b) << '\n';

    //更优解法
    ll drop = k;
    for (char c : a) {
        while (!st.empty() && drop > 0 && c < st[st.length()-1]) {
            st.pop_back(); drop--;
        }
        st.push_back(c);
    }
    st.resize(n-k);
    ll start = 0;
    while (start < st.length()-1 && st[start]=='0') start++;
    cout << st.substr(start) << '\n';
    return 0;
}
