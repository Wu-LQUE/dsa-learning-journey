#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    freopen("qkv.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,d; cin >> n >> d;
    vector<vector<ll>> Q(n+1,vector<ll> (d+1));
    vector<vector<ll>> K(n+1,vector<ll> (d+1));
    vector<vector<ll>> V(n+1,vector<ll> (d+1));
    vector<ll> W(n+1);
    //读q,k,v
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= d; ++j) {
            ll num; cin >> num;
            Q[i][j] = num;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= d; ++j) {
            ll num; cin >> num;
            K[i][j] = num;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= d; ++j) {
            ll num; cin >> num;
            V[i][j] = num;
        }
    }
    //读W
    for (int i = 1 ; i <= n; ++i) {
        ll num; cin >> num;
        W[i] = num;
    }
    //K-T(d,n) * V(n,d)-> Res(d,d) d^2 * n的时间复杂度
    vector<vector<ll>> Res(d+1,vector<ll> (d+1,0));//结果d*d
    for (int i = 1; i <= d; ++i) {
        for (int j = 1; j <= d; ++j) {
            for (int k = 1; k <= n; ++k) {
                Res[i][j] += K[k][i] * V[k][j];
            }
        }
    }

    

    //Q(n,d)与相乘Res(d,d)->(n,d)存在V(n,d)中
    V.assign(n+1,vector<ll> (d+1,0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= d; ++j) {
            for (int k = 1; k <= d; ++k) {
                V[i][j] += Q[i][k] * Res[k][j];
            }
        }
    }

    //V点乘W
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= d; ++j) {
            V[i][j] *= W[i];
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= d; ++j) {
            cout << V[i][j] << " ";
        }
        cout << endl;
    }
    
}