#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll d_arr[8][2] = {{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("dragon.txt","r",stdin);
    int n,m,p,q;
    cin >> n >> m >> p >> q;
    //1-p个人
    vector<pair<ll,ll>*> humanPos(p+1);
    for (int i = 1; i <= p; ++i) {
        pair<ll,ll> *pos = new pair<ll,ll>();
        cin >> pos->first >> pos->second;
        humanPos[i] = pos;
    }
    //q次变换
    for (int i = 1; i <= q; ++i) {
        ll x,y,t; cin >> x >> y >> t;
        //枚举龙到最近边界的距离
        ll minBarrierK = min(min(x-1,y-1),min(n-x,m-y));
        //枚举k内有无人(不包括龙原点)
        map<ll,vector<pair<ll,ll>*>> k_list;
        for (auto pos : humanPos) {
            if (!pos) continue;
            ll dx = abs(pos->first - x);
            ll dy = abs(pos->second - y);
            ll distance = max(dx,dy);
            if (distance > minBarrierK) continue;
            else if (distance == 0) continue;//原点
            else if (dx == 0 || dy == 0) k_list[distance].push_back(pos);
            else if (dx == dy) k_list[distance].push_back(pos);
        }
        //有人在范围内，取最小的那圈
        if (!k_list.empty()) {
            auto min_key_value_pair = k_list.begin();
            ll minK = min_key_value_pair->first;
            //把最里面的人做逆时针旋转t次[1,7]
            for (auto pos : min_key_value_pair->second) {
                ll dx = pos->first - x;
                ll dy = pos->second - y;
                //const ll d_arr[8][2] = {{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};
                int offNum = -1;
                if (dx == 0 && dy > 0) {
                    offNum = 2;
                }else if (dx == 0 && dy < 0) {
                    offNum = 6;
                }else if (dy == 0 && dx > 0) {
                    offNum = 0;
                }else if (dy == 0 && dx < 0) {
                    offNum = 4;
                }else if (dx > 0 && dy > 0) {
                    offNum = 1;
                }else if (dx < 0 && dy > 0) {
                    offNum = 3;
                }else if (dx < 0 && dy < 0) {
                    offNum = 5;
                }else if (dx > 0 && dy < 0) {
                    offNum = 7;
                }
                offNum = (offNum + t) % 8;
                pos->first = minK * d_arr[offNum][0] + x;
                pos->second = minK * d_arr[offNum][1] + y;
            }
        }
    }
    ll res = 0;
    for (int i = 1; i <= p; ++i) {
        pair<ll,ll> *pos = humanPos[i];
        res ^= i * pos->first + pos->second; 
    }
    cout << res << endl;
}