//P1030 [NOIP 2001 普及组] 求先序排列
#include <bits/stdc++.h>
using namespace std;
#define ll long long
//const int MAXN = 2e6 + 5;
//int a[MAXN];
string inorder; 
string afterorder; 
void dfs(int l1,int r1,int l2,int r2) {
    cout << afterorder[r2];
    int root = inorder.find(afterorder[r2]);
    int l_len = root - l1;
    int r_len = r1 - root;
    if (l_len >= 1) dfs(l1,l1 + l_len - 1,l2,l2+l_len-1);
    if (r_len >= 1) dfs(root + 1,root + r_len,r2-r_len,r2 - 1);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("P1030.txt","r",stdin);
    cin >> inorder;
    cin >> afterorder;
    dfs(0,afterorder.length()-1,0,afterorder.length()-1); 
    return 0;
}
