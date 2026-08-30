//P1419 寻找段落
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MAXN = 1e5 + 5;
int n,S,T;
double a[MAXN];
double sum[MAXN];
int q[MAXN];
bool check(double mid) {
    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i-1] + (a[i] - mid);
    }
    int head = 0,tail = 0;
    //遍历右端点i
    for (int i = S; i <= n; ++i) {
        int k = i - S;
        //弹出队尾的大值
        while (head < tail && sum[q[tail-1]] >= sum[k]) {
            tail--;
        }
        //插入小值
        q[tail++]=k;
        //除旧
        while (head < tail && q[head] < i - T) {
            head++;
        }
        //检查最小值是否符合
        if (head < tail && sum[i] - sum[q[head]] >= 0) {
            return true;
        }
    }
    return false;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1419.txt","r",stdin);
    cin >> n >> S >> T;
    double l = 1e9,r = -1e9;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] < l) l = a[i];
        if (a[i] > r) r = a[i];
    }

    //二分答案
    for (int it = 0; it < 70; it++) {
        double mid = l + (r-l)/2.0;
        if (check(mid)) {
            l = mid;
        }else {
            r = mid;
        }
    }

    cout << fixed << setprecision(3) << l << '\n';
    return 0;
}
