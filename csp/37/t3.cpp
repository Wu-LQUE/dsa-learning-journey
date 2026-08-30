#include <bits/stdc++.h>
using namespace std;
#define ll long long
// const int N = 1e5+10;
ll n;
const ll mod = 1000000007;
unordered_map<string,string> vars; //存表达式的字面量直接转换成数字
unordered_map<string,bool> isConst;
ll calc(string expr) {
    ll res=0;
    string token;
    stringstream ss(expr);
    // ss >> ws;
    while (ss >> token) {
        if (token[0]=='$') {
            string var = token.substr(1);
            if (isConst[var]) res += stoll(vars[var]);
            else res += calc(vars[var]);
            res %= mod;
        } else {
            res += stoll(token);
            res %= mod;
        }
        // ss >> ws;
    }
    return res;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t3.txt","r",stdin);
    cin >> n; cin.ignore();
    string line,var,expr;
    stringstream ss;
    ll op;
    while (n--) {
        getline(cin,line); ss.clear(); ss.str(line);
        ss >> op >> var;
        getline(ss,expr);
        if (op == 1) {
            ll tot = 0;
            string token;
            stringstream ss2(expr);
            while (ss2 >> token) {
                if (token[0]=='$') {
                    string var = token.substr(1);
                    tot += calc(vars[var]);
                    tot %= mod;
                } else {
                    tot += token.length();
                    tot %= mod;
                }
            }
            vars[var] = to_string(tot);
            isConst[var] = 1;
        }else if (op == 2) {
            ll tot = 0;
            string token;
            string tmp;
            stringstream ss2(expr);
            while (ss2 >> token) {
                if (token[0]=='$') {
                    tmp += (token+" "); 
                } else {
                    tot += token.length();
                    tot %= mod;
                }
            }
            vars[var] = tot + " " + tmp;
            isConst[var] = 0;
        }else if (op == 3) {
            if (isConst[var]) cout << stoll(vars[var]) % mod << '\n';
            else cout << calc(vars[var]) % mod << '\n';
        }
    }
}