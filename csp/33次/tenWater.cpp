#include <bits/stdc++.h>
using namespace std;

//暴力
// const int maxSize = 10000005;
// int nums[maxSize];
// int main() {
//     freopen("tenWater.txt","r",stdin);
//     int arrLen,n,m;
//     // cin >> arrLen; cin >> n; cin >> m;
//     cin >> arrLen >> n >> m;
//     if (arrLen > maxSize) return 0;
//     int pos,num;
//     for (int i = 1; i <= n; ++i) {
//         // cin >> pos; cin >> num;
//         cin >> pos >> num;
//         nums[pos] = num;
//     }
//     for (int i = 1; i <= m; ++i) {
//         cin >> pos;
//         nums[pos]++;
//         if (nums[pos]>=5) {
//             nums[pos] = 0;
//             n--;
//             //左边检查
//             for (int i = pos-1; i>=1; --i) {
//                 if (nums[i]!=0) {
//                     nums[i]++;
//                     break;
//                 }
//             }
//             //右边
//             for (int i = pos+1; i <= arrLen; ++i) {
//                 if (nums[i]!=0) {
//                     nums[i]++;
//                     break;
//                 }
//             }
//             //循环处理这一轮
//             int checkFinished = false;
//             while (!checkFinished) {
//                 int i = 1;
//                 for ( ;i <= arrLen; ++i) {
//                     if (nums[i]>=5) {
//                         nums[i] = 0;
//                         n--;
//                         //左边增加
//                         for (int j = pos-1; j>=1; --j) {
//                             if (nums[j]!=0) {
//                                 nums[j]++;
//                                 break;
//                             }
//                         }
//                         //右边增加
//                         for (int j = pos+1; j <= arrLen; ++j) {
//                             if (nums[j]!=0) {
//                                 nums[j]++;
//                                 break;
//                             }
//                         }
//                         break;
//                     }
//                 }
//                 if (i == arrLen + 1) {
//                     checkFinished = true;
//                 }
//             }
//         }
//         cout << n << endl;
//     }
//     return 0;
// }


int main() {
    freopen("tenWater.txt","r",stdin);
    map<int,int> mp;//存有水的格子
    int total,n,m;
    cin >> total >> n >> m;
    for (int i = 1; i <= n; ++i) {
        int pos,num;
        cin >> pos >> num;
        mp[pos] = num;
    }
    for (int i = 1; i <= m; ++i) {
        int pos; cin >> pos;
        mp[pos]++;
        if (mp[pos]>=5) {
            deque<int> dq;//双向队列存爆掉的水
            dq.push_front(pos);
            set<int> s;//记录队列的水
            s.insert(pos);
            while (dq.size()>0) {
                //爆掉队首的水
                int head = dq.front();
                // mp[head] = 0;
                dq.pop_front();
                mp.erase(head);
                s.erase(head);
                //先找右边的水，放队列头
                auto it = mp.upper_bound(head);
                if (it != mp.end()) {
                    mp[it->first]++;
                    if (mp[it->first]>=5 && !s.count(it->first)) {
                        dq.push_front(it->first);
                        s.insert(it->first);
                    }
                }
                //找左边的水
                it = mp.lower_bound(head);
                if (it != mp.begin()) {
                    it--;
                    mp[it->first]++;
                    if (mp[it->first]>=5 && !s.count(it->first)) {
                        dq.push_front(it->first);
                        s.insert(it->first);
                    }
                }
            }
        }
        cout << mp.size() << endl;
    }
}