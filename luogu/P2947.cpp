//P2947 [USACO09MAR] Look Up S
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 1e6 + 5;
int a[MAXN];
int b[MAXN] = {0};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P2947.txt","r",stdin);
    int n; cin >> n;
    stack<int> st;
    for (int i = 1; i <= n; ++i) {
        int h; cin >> h; a[i] = h;
        while (!st.empty() && a[st.top()] < h) {
            b[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    for (int i = 1; i <= n; ++i) cout << b[i] <<'\n';
    return 0;
}
