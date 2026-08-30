//P1229 遍历问题
#include <bits/stdc++.h>
using namespace std;
#define ll long long
//const int MAXN = 2e6 + 5;
//int a[MAXN];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1229.txt","r",stdin);
    string s1; string s2; cin >> s1; cin >> s2;
    int ans=0;
    for (int i = 0; i < s1.length()-1; ++i) 
        for (int j = 1; j < s2.length(); ++j)
            if (s1[i]==s2[j]&&s1[i+1]==s2[j-1]) ans++;
    cout << (1 << ans);
    return 0;
}
