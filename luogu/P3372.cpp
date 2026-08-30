//P3372 【模板】线段树 1
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 1e5 + 5;
ll a[MAXN];
ll tree[MAXN<<2];
ll tag[MAXN<<2];
ll ls(ll p) {return p << 1;}
ll rs(ll p) {return (p << 1) | 1;}
void pushUp(ll p) {
    tree[p] = tree[ls(p)] + tree[rs(p)];
}
void build(ll p,ll pl,ll pr) { //p是节点编号，指向区间[pl,pr]
    tag[p] = 0;
    if (pl == pr) {tree[p] = a[pl]; return;}
    ll mid = (pl + pr) >> 1;
    build(ls(p),pl,mid);
    build(rs(p),mid+1,pr);
    pushUp(p);
}
void addTag(ll p,ll pl,ll pr,ll d) {
    tag[p] += d;//tag标记
    tree[p] += d * (pr - pl + 1);//计算新的tree
}
void pushDown(ll p,ll pl,ll pr) {
    if (tag[p]) {
        ll mid = (pl + pr) >> 1;
        addTag(ls(p),pl,mid,tag[p]);
        addTag(rs(p),mid+1,pr,tag[p]);
        tag[p]=0;
    }
}
void update(ll L,ll R,ll p,ll pl,ll pr,ll d) {
    //完全覆盖
    if (L <= pl && pr <= R) {
        addTag(p,pl,pr,d);
        return;
    }
    pushDown(p,pl,pr);
    ll mid = (pl + pr) >> 1;
    if (L <= mid) update(L,R,ls(p),pl,mid,d);
    if (R > mid) update(L,R,rs(p),mid+1,pr,d);
    pushUp(p);
}
ll query(ll L,ll R,ll p,ll pl,ll pr) {
    if (L <= pl && pr <= R) return tree[p];
    pushDown(p,pl,pr);
    ll res=0;
    ll mid = (pl + pr) >> 1;
    if (L <= mid) res+=query(L,R,ls(p),pl,mid);
    if (R > mid) res+=query(L,R,rs(p),mid+1,pr);
    return res;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P3372.txt","r",stdin);
    ll n,m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1,1,n);
    while (m--) {
        ll q,x,y,k; cin >> q;
        if (q == 1) {
            cin >> x >> y >> k;
            update(x,y,1,1,n,k);
        }
        else {
            cin >> x >> y;
            cout << query(x,y,1,1,n) << '\n';
        }
    }
    return 0;
}
