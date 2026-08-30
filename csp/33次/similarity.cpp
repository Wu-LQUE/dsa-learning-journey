#include <bits/stdc++.h>
#include <algorithm>
#include <cctype>

using namespace std;
typedef long long ll;
int main() {
    freopen("sim.txt","r",stdin);
    int page1wordCount,page2wordCount;
    cin >> page1wordCount;
    cin >> page2wordCount;
    //读第一篇文章
    unordered_set<string> set1;
    for (int i = 0; i < page1wordCount; ++i) {
        string strKey;
        cin >> strKey;
        transform(strKey.begin(), strKey.end(), strKey.begin(), ::tolower);
        set1.insert(strKey);
    }
    //读第二篇文章
    unordered_set<string> set2;
    for (int i = 0; i < page2wordCount; ++i) {
        string strKey;
        cin >> strKey;
        transform(strKey.begin(), strKey.end(), strKey.begin(), ::tolower);
        set2.insert(strKey);
    }
    //计算交集
    int intersection_size = 0;
    for (const auto &w : set1) {
        if (set2.find(w)!=set2.end()) {
            intersection_size++;
        }
    }
    //计算并集
    for (const auto &w : set1) {
        set2.insert(w);
    }
    cout << intersection_size << endl << set2.size(); 
}