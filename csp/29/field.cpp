#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("field.txt","r",stdin);
    int n; cin >> n;
    int a,b; cin >> a >> b;//0 0 -> a b
    vector<pair<int,int>*> fieldsLeftDown(n);
    vector<pair<int,int>*> fieldsRightUp(n);
    for (int i = 0; i < n; ++i) {
        int x1,y1; cin >> x1 >> y1;
        int x2,y2; cin >> x2 >> y2;
        // pair<int,int> *xy = new pair<int,int>();
        pair<int,int> *x1y1 = new pair<int,int>(x1,y1);
        pair<int,int> *x2y2 = new pair<int,int>(x2,y2);
        fieldsLeftDown[i] = x1y1;
        fieldsRightUp[i] = x2y2;
    }
    ull totalS = 0;
    for (int i = 0; i < n; ++i) {
        pair<int,int> x1y1 = *fieldsLeftDown[i];
        pair<int,int> x2y2 = *fieldsRightUp[i];
        int up = min(x2y2.second,b);
        int down = max(x1y1.second,0);
        int left = max(x1y1.first,0);
        int right = min(x2y2.first,a);
        ll square = (up - down) * (right - left);
        if (square > 0 && (up > down && right > left)) totalS += square;        
    }
    cout << totalS << endl;
}
