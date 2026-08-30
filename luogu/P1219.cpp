//P1219 [USACO1.5] 八皇后 Checker Challenge
#include <bits/stdc++.h>
using namespace std;
#define ll long long
//const int MAXN = 2e6 + 5;
//int a[MAXN];
int n,tot = 0;
vector<vector<int>> ans;
vector<int> col;
vector<int> diag1;
vector<int> diag2;
vector<int> record;
void dfs(int i) {
    if (i==n) {
        ans.push_back(record);
        tot++;
        return;
    }
    for (int j = 0; j < n; ++j) {
        if (!col[j] && !diag1[j - i + n] && !diag2[i + j]) {
            // state[i][j] = 1;
            col[j] = 1;
            diag1[j - i + n] = 1;
            diag2[i + j] = 1;
            record.push_back(j+1);
            dfs(i+1);
            // state[i][j] = 0;
            col[j] = 0;
            diag1[j - i + n] = 0;
            diag2[i + j] = 0;
            record.pop_back();
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1219.txt","r",stdin);
    cin >> n;
    // vector<vector<int>> *state = new vector<vector<int>>(n,vector<int>(n));
    vector<vector<int>> state(n,vector<int>(n));
    col.resize(n); diag1.resize(2*n+5); diag2.resize(2*n+5);
    dfs(0);
    for (int i = 0; i < min(3,(int)ans.size()); ++i) {
        for (int j = 0; j < n; ++j) {
            cout << ans[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << tot << '\n';
    return 0;
}
