#include <bits/stdc++.h>
using namespace std;
/* 最大容量接水问题：贪心 */
int maxCapacity(vector<int> &ht) {
    int i = 0,j = ht.size()-1;
    int maxVolume = -1;
    while (j>i) {
        int shortHt = min(ht[i],ht[j]);
        int volume = (j - i) * shortHt;
        maxVolume = max(volume,maxVolume);
        if (shortHt == ht[i]) {
            i++;
        }else {
            j--;
        }
    }
}