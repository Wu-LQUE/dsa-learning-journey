#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("mtkl.txt","r",stdin);
    int pointNum;
    double a;
    cin >> pointNum; cin >> a;
    int m = 0;
    double aa = a * a;
    for (int i = 0; i < pointNum; ++i) {
        double x,y;
        cin >> x; cin >> y;
        double dd = x * x + y * y;
        if (dd <= aa) {
            m++;
        }
    }
    printf("%.6f",4*m/(double)pointNum);
}