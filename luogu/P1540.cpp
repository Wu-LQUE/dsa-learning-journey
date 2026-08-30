#include <bits/stdc++.h>
using namespace std;
#define ll long long
int Hash[1003] = {0};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1540.txt","r",stdin);
    int m,n; cin >> m >> n;
    queue<int> memo;
    int cnt = 0;
    for (int i = 1; i <= n; ++i) {
        int num; cin >> num;
        if (Hash[num] == 0) {
            Hash[num] = 1;
            cnt++;
            memo.push(num);
            if (memo.size() > m) {
                int popNum = memo.front();
                memo.pop();
                Hash[popNum] = 0;
            }
        }
    }
    cout << cnt;
}
