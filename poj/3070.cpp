#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2;
struct matrix { int m[N][N]; };
ll m = 10000;
matrix operator * (const matrix& a,const matrix& b) {
    matrix c;
    memset(c.m,0,sizeof(c.m));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) 
            for (int k = 0; k < N; ++k) 
                c.m[i][j] =(c.m[i][j] + a.m[i][k] * b.m[k][j]) % m;
    return c;
}
matrix fmpow(matrix a,int n) {
    matrix ans;
    memset(ans.m,0,sizeof(ans.m));
    for (int i = 0; i < N; ++i) ans.m[i][i] = 1;
    while (n) {
        if (n&1) ans = ans * a;
        a = a * a;
        n >>= 1;
    }
    return ans;
}
matrix aa;
ll solve(ll n) {
    return fmpow(aa,n).m[1][0];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n;
    aa.m[0][0] = 1; aa.m[0][1] = 1; aa.m[1][0] = 1; aa.m[1][1] = 0;
    while (true) {
        cin >> n;
        if (n == -1) break;
        cout << solve(n) << '\n';
    }
}