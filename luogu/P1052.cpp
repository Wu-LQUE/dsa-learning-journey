//P1052 [NOIP 2005 提高组] 过河
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 1e6 + 5;
int a[MAXN];
int dp[MAXN];
ll L,S,T,M;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1052.txt","r",stdin);
    cin >> L >> S >> T >> M;
    ll last,cur,pos=0;
    int stone[M+1];
    for (int i = 1; i <= M; ++i) cin >> stone[i];
    sort(stone+1,stone+1+M);

    if (S==T) {
        ll ans = 0;
        for (int i = 1; i <= M; ++i) {
            if (stone[i]%S==0) ans++;
        }
        cout << ans;
        return 0;
    }

    for (int i = 1; i <= M; ++i) {
        cur = stone[i];
        if (i==1) {
            if (cur>1001) {
                pos += 1001;
                a[pos] = 1;
            }else {
                pos = cur;
                a[pos] = 1;
            }
        }else if (cur-last>1001) {
            pos += 1001;
            a[pos] = 1;
        }else {
            pos += cur - last;
            a[pos] = 1;
        }
        last = cur;
    }
    ll end = pos; int minStep = INT_MAX;
    for (int i = 1; i <= end+T+1; ++i) {
        int best = 100;
        for (int j = i-T; j <= i-S; ++j) {
            if (j<0) continue;
            if (dp[j]<best) best = dp[j];
        }
        dp[i] = best + a[i];
        if (i>=end) {
            minStep = min(minStep,dp[i]);
        }
    }
    cout << minStep;
    return 0;
}
