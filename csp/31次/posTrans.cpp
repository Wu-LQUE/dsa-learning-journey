#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("posTrans.txt","r",stdin);
    int n,m; cin >> n >> m;
    int dx=0,dy = 0;
    for (int i = 0; i < n; ++i) {
        int a,b; cin >> a >> b;
        dx+=a;
        dy+=b;
    }
    for(int i = 0; i < m; ++i) {
        int x,y; cin >> x >> y;
        cout << x+dx << " " << y+dy << endl;
    }

}