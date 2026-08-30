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
    vector<vector<ll>> Res(n+1,vector<ll> (n+1,0));//结果n*n
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= d; ++k) {
                Res[i][j] += Q[i][k] * K[j][k];
            }
        }
    }
    //Res点乘W
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            Res[i][j] *= W[i];
        }
    }
    //Res(n,n)与V(n,d)相乘(n,d)存在Q(n,d)中
    Q.assign(n+1,vector<ll> (d+1,0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= d; ++j) {
            for (int k = 1; k <= n; ++k) {
                Q[i][j] += Res[i][k] * V[k][j];
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= d; ++j) {
            cout << Q[i][j] << " ";
        }
        cout << endl;
    }
    
}