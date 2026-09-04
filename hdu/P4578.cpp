#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100000 + 5;
const int MOD = 10007;

ll sum1[N << 2], sum2[N << 2], sum3[N << 2];
ll tagadd[N << 2], tagmul[N << 2], tagchg[N << 2];

ll ls(ll p) { return (p << 1); }
ll rs(ll p) { return (p << 1) | 1; }

void push_up(ll p) {
    sum1[p] = (sum1[ls(p)] + sum1[rs(p)]) % MOD;
    sum2[p] = (sum2[ls(p)] + sum2[rs(p)]) % MOD;
    sum3[p] = (sum3[ls(p)] + sum3[rs(p)]) % MOD;
}

void build(ll p, ll pl, ll pr) {
    tagadd[p] = 0; tagchg[p] = -1; tagmul[p] = 1;
    if (pl == pr) {
        sum1[p] = sum2[p] = sum3[p] = 0;
        return;
    }
    ll mid = (pl + pr) >> 1;
    build(ls(p), pl, mid);
    build(rs(p), mid + 1, pr);
    push_up(p);
}

void chgtag(ll p, ll pl, ll pr, ll d) {
    d %= MOD;
    ll len = (pr - pl + 1) % MOD;
    sum1[p] = len * d % MOD;
    sum2[p] = sum1[p] * d % MOD;
    sum3[p] = sum2[p] * d % MOD;
    tagadd[p] = 0;
    tagmul[p] = 1;
    tagchg[p] = d;
}

void addtag(ll p, ll pl, ll pr, ll d) {
    d %= MOD;
    if (tagchg[p] != -1) {
        chgtag(p, pl, pr, (tagchg[p] + d) % MOD);
        return;
    }
    ll len = (pr - pl + 1) % MOD;
    ll s1 = sum1[p], s2 = sum2[p], s3 = sum3[p];
    sum1[p] = (s1 + len * d % MOD) % MOD;
    sum2[p] = (s2 + 2 * s1 % MOD * d % MOD + len * d % MOD * d % MOD) % MOD;
    sum3[p] = (s3 + len * d % MOD * d % MOD * d % MOD 
                + 3 * d % MOD * ((s2 + s1 * d % MOD) % MOD) % MOD) % MOD;
    tagadd[p] = (tagadd[p] + d) % MOD;
}

void multag(ll p, ll pl, ll pr, ll d) {
    d %= MOD;
    if (tagchg[p] != -1) {
        chgtag(p, pl, pr, tagchg[p] * d % MOD);
        return;
    }
    tagadd[p] = tagadd[p] * d % MOD;
    tagmul[p] = tagmul[p] * d % MOD;
    sum1[p] = sum1[p] * d % MOD;
    sum2[p] = sum2[p] * d % MOD * d % MOD;
    sum3[p] = sum3[p] * d % MOD * d % MOD * d % MOD;
}

void push_down(ll p, ll pl, ll pr) {
    ll mid = (pl + pr) >> 1;
    if (tagchg[p] != -1) {
        chgtag(ls(p), pl, mid, tagchg[p]);
        chgtag(rs(p), mid + 1, pr, tagchg[p]);
        tagchg[p] = -1;
    }
    if (tagmul[p] != 1 || tagadd[p] != 0) {
        multag(ls(p), pl, mid, tagmul[p]);
        addtag(ls(p), pl, mid, tagadd[p]);
        multag(rs(p), mid + 1, pr, tagmul[p]);
        addtag(rs(p), mid + 1, pr, tagadd[p]);
        tagmul[p] = 1;
        tagadd[p] = 0;
    }
}

void updateAdd(ll L, ll R, ll p, ll pl, ll pr, ll d) {
    if (L <= pl && pr <= R) {
        addtag(p, pl, pr, d);
        return;
    }
    push_down(p, pl, pr);
    ll mid = (pl + pr) >> 1;
    if (L <= mid) updateAdd(L, R, ls(p), pl, mid, d);
    if (R >= mid + 1) updateAdd(L, R, rs(p), mid + 1, pr, d);
    push_up(p);
}

void updateMul(ll L, ll R, ll p, ll pl, ll pr, ll d) {
    if (L <= pl && pr <= R) {
        multag(p, pl, pr, d);
        return;
    }
    push_down(p, pl, pr);
    ll mid = (pl + pr) >> 1;
    if (L <= mid) updateMul(L, R, ls(p), pl, mid, d);
    if (R >= mid + 1) updateMul(L, R, rs(p), mid + 1, pr, d);
    push_up(p);
}

void updateChg(ll L, ll R, ll p, ll pl, ll pr, ll d) {
    if (L <= pl && pr <= R) {
        chgtag(p, pl, pr, d);
        return;
    }
    push_down(p, pl, pr);
    ll mid = (pl + pr) >> 1;
    if (L <= mid) updateChg(L, R, ls(p), pl, mid, d);
    if (R >= mid + 1) updateChg(L, R, rs(p), mid + 1, pr, d);
    push_up(p);
}

ll query(ll L, ll R, ll p, ll pl, ll pr, ll c) {
    if (L <= pl && pr <= R) {
        if (c == 1) return sum1[p];
        else if (c == 2) return sum2[p];
        else return sum3[p];
    }
    push_down(p, pl, pr);
    ll res = 0;
    ll mid = (pl + pr) >> 1;
    if (L <= mid) res = (res + query(L, R, ls(p), pl, mid, c)) % MOD;
    if (R >= mid + 1) res = (res + query(L, R, rs(p), mid + 1, pr, c)) % MOD;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    ll n, m;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) break;
        build(1, 1, n);
        ll op, x, y, z;
        while (m--) {
            cin >> op >> x >> y >> z;
            if (op == 1) {
                updateAdd(x, y, 1, 1, n, z);
            } else if (op == 2) {
                updateMul(x, y, 1, 1, n, z);
            } else if (op == 3) {
                updateChg(x, y, 1, 1, n, z);
            } else if (op == 4) {
                cout << query(x, y, 1, 1, n, z) << '\n';
            }
        }
    }
    return 0;
}