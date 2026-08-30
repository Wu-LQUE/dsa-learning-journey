#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define endl "\n"
struct expression {
    bool isComplex;
    char logic;//"&" / "|"
    expression *left;
    expression *right;
    
    bool isBase;
    ll attr;
    char op;//":" / "~"
    ll value;
};

expression *newExpr() {
    expression *tmp = new expression();
    tmp->isComplex = tmp->isBase = false;
    tmp->logic = tmp->op = '\0';
    tmp->left = tmp->right = nullptr;
    tmp->attr = tmp->value = 0;
    return tmp;
}

expression *parseBaseExpr(stringstream &ss) {
    expression *tmp = newExpr();
    tmp->isBase = true;
    ss >> tmp->attr >> tmp->op >> tmp->value;
    return tmp;
}

expression *parseExpr(stringstream &ss) {
    if (isdigit(ss.peek())) {//基本表达式
        return parseBaseExpr(ss);
    }else {//复合表达式
        expression *tmp = newExpr();
        tmp->isComplex = true;
        ss >> tmp->logic;
        ss.ignore(1);//跳过左括号
        expression *left = parseExpr(ss);//左边表达式
        ss.ignore(1);//跳过右括号

        ss.ignore(1);//跳过左括号
        expression *right = parseExpr(ss);
        ss.ignore(1);//跳过右括号

        tmp->left = left; tmp->right = right;
        return tmp;
    }
    
}
bool matchExp(expression *expr,map<ll,ll> &kv) {
    if (expr->isBase) {
        if (expr->op==':') return kv.count(expr->attr) && kv[expr->attr] == expr->value;
        else if (expr->op=='~') return kv.count(expr->attr) && kv[expr->attr] != expr->value;
    }else if (expr->isComplex) {
        bool leftMatch=matchExp(expr->left,kv),rightMatch=matchExp(expr->right,kv);
        if (expr->logic=='&') return leftMatch && rightMatch;
        else if (expr->logic=='|') return leftMatch || rightMatch;
    }
    return false;
}

bool cmp() {
    
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("ldap.txt","r",stdin);
    ll n; cin >> n;
    vector<map<ll,ll>> usrKV(n+1);
    vector<ll> dn_list(n+1);
    for (int i = 1; i <= n; ++i) {
        ll dn; cin >> dn;
        dn_list[i] = dn;
        ll kvNum; cin >> kvNum;
        while (kvNum > 0) {
            ll k,v; cin >> k >> v;
            usrKV[i][k] = v;
            kvNum--;
        }
    }
    ll m; cin >> m;
    cin.ignore();
    for (int i = 0; i < m; ++i) {
        string tmp; getline(cin,tmp);
        stringstream strExp(tmp);
        expression *exp = parseExpr(strExp);
        set<ll> matchSet;
        for (int j = 1; j <= n; ++j) {
            map<ll,ll> &usr = usrKV[j];
            if (matchExp(exp,usr)) matchSet.insert(dn_list[j]);
        }
        for (ll dn : matchSet) {
            cout << dn << " ";
        }
        cout << endl;
    }

}