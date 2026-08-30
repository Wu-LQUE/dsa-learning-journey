#include <bits/stdc++.h>
using namespace std;

int main(){
    freopen("cangku.txt","r",stdin);
    int n,m; cin >> n >> m;
    vector<vector<int>> vecArr(n+1,vector<int>(m));
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < m; ++j) {
            int num; cin >> num;
            vecArr[i][j] = num;
        }
    }
    for (int i = 1; i <= n; ++i) {
        vector<int> cangku = vecArr[i];
        int isParent = 1;
        for (int i2 = 1; i2 <=n; ++i2) {
            if (i2 == i) continue;
            isParent = 1;
            for (int j = 0; j < m; ++j) {
                if (vecArr[i2][j] <= cangku[j]) {
                    isParent = 0;
                    break;
                }
            }
            if (!isParent) {
                continue;
            }else {
                cout << i2 << endl;
                break;
            }
        }
        if (!isParent) {
            cout << 0 << endl;
        }
    }
}