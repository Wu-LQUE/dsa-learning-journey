//P1162 填涂颜色
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define x first 
#define y second
//const int MAXN = 2e6 + 5;
//int a[MAXN];
int n;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1162.txt","r",stdin);
    cin >> n;
    vector<vector<int>> mp(n,vector<int>(n));
    queue<pair<int,int>> q;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) cin >> mp[i][j];
    for (int i=0,j=0; j < n; ++j) {
        if (mp[i][j] == 0) q.push({i,j});
    }
    for (int i=n-1,j=0; j < n; ++j) {
        if (mp[i][j] == 0) q.push({i,j});
    }
    for (int j=0,i=0; i < n; ++i) {
        if (mp[i][j] == 0) q.push({i,j});
    }
    for (int j=n-1,i=0; i < n; ++i) {
        if (mp[i][j] == 0) q.push({i,j});
    }

    while (!q.empty()) {
        pair<int,int> tmp = q.front(); q.pop();
        mp[tmp.x][tmp.y] = 3; // 边缘0染色为3
        if (tmp.y - 1 >= 0 && mp[tmp.x][tmp.y-1] == 0) q.push({tmp.x,tmp.y-1});
        if (tmp.y + 1 <= n-1 && mp[tmp.x][tmp.y+1] == 0) q.push({tmp.x,tmp.y+1});
        if (tmp.x - 1 >= 0 && mp[tmp.x-1][tmp.y] == 0) q.push({tmp.x-1,tmp.y});
        if (tmp.x + 1 <= n-1 && mp[tmp.x+1][tmp.y] == 0) q.push({tmp.x+1,tmp.y});
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (mp[i][j] == 3) cout << 0;
            if (mp[i][j] == 0) cout << 2;
            if (mp[i][j] == 1) cout << 1;
            cout << ' ';
        }
        cout << '\n';
    }
    return 0;
}
