#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t1.txt","r",stdin);
    ll n,k;
    cin >> n >> k;
    while (k--) {
        ll x,y; cin >> x >> y;
        string move; cin >> move;
        for (char &ch : move) {
            if (ch == 'f' && y+1<=n) y++;
            else if (ch == 'b' && y-1>=1) y--;
            else if (ch == 'l' && x-1>=1) x--;
            else if (ch == 'r' && x+1<=n) x++;
        }
        cout << x << ' ' << y << '\n';
    }
}