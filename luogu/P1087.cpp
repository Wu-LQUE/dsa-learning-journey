//P1087 [NOIP 2004 普及组] FBI 树
#include <bits/stdc++.h>
using namespace std;
#define ll long long
string a;

char dfs(int l, int r) {
    int mid = (l + r) / 2;
    if (l == r) {
        if (a[l] == '0') {
            cout << 'B';
            return 'B';
        } else {
            cout << 'I';
            return 'I';
        }
    } else {
        char lc = dfs(l, mid);
        char rc = dfs(mid + 1, r);
        
        if (lc == 'B' && rc == 'B') {
            cout << 'B';
            return 'B';
        } else if (lc == 'I' && rc == 'I') {
            cout << 'I';
            return 'I';
        } else {
            cout << 'F';
            return 'F';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1087.txt","r",stdin);
    int n; 
    cin >> n;
    int r = pow(2, n) - 1;
    cin >> a;
    dfs(0, r);
    cout << endl;  // 添加换行
    return 0;
}