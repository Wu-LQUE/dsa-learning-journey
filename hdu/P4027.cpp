#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 100000+5;
ll a[N];
ll tree[N<<2];
ll ls(ll p) {return (p << 1);}
ll rs(ll p) {return (p << 1) | 1;}

void push_up(ll p) {
    tree[p] = tree[ls(p)] + tree[rs(p)];
}

void build(ll p,ll pl,ll pr) {
    if (pl==pr) {tree[p] = a[pl]; return;}
    ll mid = (pl + pr) >> 1;
    build(ls(p),pl,mid);
    build(rs(p),mid+1,pr);
    push_up(p);
}

void kf(ll p,ll pl,ll pr) {
    if (tree[p]==pr-pl+1) return;
    if (pl==pr) {tree[p] = sqrt(tree[p]);return;}
    ll mid = (pl + pr) >> 1;
    kf(ls(p),pl,mid);
    kf(rs(p),mid+1,pr);
    push_up(p);
}

void update(ll L,ll R,ll p,ll pl,ll pr) {
    if (L <= pl && pr <= R) {
        kf(p,pl,pr);
        return;
    }
    ll mid = (pl + pr) >> 1;
    if (L <= mid) update(L,R,ls(p),pl,mid);
    if (R >= mid+1) update(L,R,rs(p),mid+1,pr);
    push_up(p);
}

ll query(ll L,ll R,ll p,ll pl,ll pr) {
    if (L <= pl && pr <= R) return tree[p];
    ll res = 0;
    ll mid = (pl + pr) >> 1;
    if (L <= mid) res += query(L,R,ls(p),pl,mid);
    if (R >= mid + 1) res += query(L,R,rs(p),mid + 1,pr);
    return res;
}

ll n,m;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // freopen("4027.txt","r",stdin);
    int caseNo = 0;
    while (cin >> n) {
        ++caseNo;
        for (int i = 1; i <= n; ++i) cin >> a[i];
        build(1,1,n);
        cin >> m;
        ll t,x,y;
        cout << "Case #" << caseNo << ":\n";
        while (m--) {
            cin >> t >> x >> y;
            if (x > y) swap(x, y);
            if (t == 0) {
                update(x,y,1,1,n);
            } else if (t == 1) {
                cout << query(x,y,1,1,n) << '\n';
            }
        }
        cout << '\n';
    }
    return 0;
}