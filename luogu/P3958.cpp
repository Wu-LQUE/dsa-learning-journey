//P3958 [NOIP 2017 提高组] 奶酪
#include <bits/stdc++.h>
#include <cstring>
using namespace std;
#define ll long long
#define ull unsigned long long
#define dis(i,j,pp) ((c[i].pp-c[j].pp)*(c[i].pp-c[j].pp))
struct circle{
    ll x,y,z;
    bool up,down;
}c[1005];
int fa[1005];
bool edge[1005][1005];
ll t,n,h,r;
int findset(int x) {
    if (x != fa[x]) {
        int t = fa[x];
        fa[x] = findset(fa[x]);
    }
    return fa[x];
}
void hb(int x, int y) {
    int fx = findset(x),fy = findset(y);
    fa[fx] = fy;
    if (fx != fy) {
        c[fy].up = c[fy].up || c[fx].up;
        c[fy].down = c[fy].down || c[fx].down;
        fa[fx] = fy;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("P3958.txt","r",stdin);

    long long T;
    cin >> T;

    while (T--) {
        long long n, h, r;
        cin >> n >> h >> r;

        for (int i = 1; i <= n; ++i) fa[i] = i;

        for (int i = 1; i <= n; ++i) {
            cin >> c[i].x >> c[i].y >> c[i].z;
            c[i].up = (c[i].z + r >= h);
            c[i].down = (c[i].z <= r);
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                __int128 dx = (__int128)c[i].x - c[j].x;
                __int128 dy = (__int128)c[i].y - c[j].y;
                __int128 dz = (__int128)c[i].z - c[j].z;

                if (4 * (__int128)r * r >= dx * dx + dy * dy + dz * dz) {
                    hb(i, j);
                }
            }
        }

        bool ans = false;
        for (int i = 1; i <= n; ++i) {
            if (c[i].up && c[i].down) {
                ans = true;
                break;
            }
        }

        cout << (ans ? "Yes\n" : "No\n");
    }

    return 0;
}
