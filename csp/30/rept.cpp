#include <bits/stdc++.h>
using namespace std;
void getJu(string &str) {
    for (int i = 0; i < 8; ++i) {
        string tmp;
        getline(cin,tmp);
        str.append(tmp);
    }
}
int main() {
    freopen("rept.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    unordered_map<string,int> ctMap;
    int n; cin >> n;
    cin.ignore();
    for (int i = 0; i < n; ++i) {
        string k;
        getJu(k);
        ctMap[k]++;
        cout << ctMap[k] << endl;
    }
    return 0;
}