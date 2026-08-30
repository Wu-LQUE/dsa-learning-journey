#include <bits/stdc++.h>
using namespace std;
#define ll long long
inline ll modResult(ll res) {
    ll modNumber = (ll)(1e9 + 7);
    ll result = res % modNumber;
    if (result < 0) result += modNumber;
    return result;
}

struct expression {
    //表达式
    bool isExp;
    expression *left;
    char op;
    expression *right;

    bool isX;//data当作序号
    bool isConst;//data当作常数
    ll data;//序号1-n或者常数
};

ll calExpression(expression &expr,vector<ll> &a_list) {
    if (expr.isX) return a_list[expr.data];
    else if (expr.isConst) return expr.data;
    else if (expr.isExp) {
        ll left = calExpression(*expr.left,a_list);
        ll right = calExpression(*expr.right,a_list);
        ll result;
        switch (expr.op)
        {
        case '+':
            result = modResult( modResult(left) + modResult(right));
            break;
        case '-':
            result = modResult( modResult( left )- modResult(right));
            break;
        case '*':
            result = modResult( modResult(left) * modResult(right));
            break;
        default:
            break;
        }
        return result;
    }
}

ll daoExpression(expression &expr,vector<ll> &a_list,ll x_number) {
    //对单一节点求导
    if (expr.isX) {
        if (expr.data == x_number) return 1;
        else return 0;//当常数
    }
    else if (expr.isConst) return 0;
    else if (expr.isExp) {
        char op = expr.op;
        expression *left = expr.left;
        expression *right = expr.right;
        ll leftResult,rightResult,finalResult;
        if (op == '+') {
            finalResult = modResult( modResult(daoExpression(*left,a_list,x_number)) + modResult(daoExpression(*right,a_list,x_number)) );
        }else if (op == '-') {
            finalResult = modResult( modResult(daoExpression(*left,a_list,x_number)) - modResult(daoExpression(*right,a_list,x_number)) );
        }else if (op == '*') {
            leftResult = modResult( modResult(daoExpression(*left,a_list,x_number)) * modResult(calExpression(*right,a_list)) );
            rightResult = modResult( modResult(calExpression(*left,a_list)) * modResult(daoExpression(*right,a_list,x_number)) );
            finalResult = modResult( modResult(leftResult) + modResult(rightResult) );
        }
        return finalResult;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("csp31t3.txt","r",stdin);
    int n,m; cin >> n >> m;
    vector<ll> a_list(n+1);//n个变量对应值
    //读一个逆波兰表达式
    stack<expression*> stk;  // 改为存储指针
    string polish_re_expr;
    cin.ignore();
    getline(cin,polish_re_expr);
    stringstream ss(polish_re_expr);
    
    vector<expression*> all_expressions; // 用于内存管理
    
    while(!ss.eof()) {
        string element;
        ss >> element;
        //构建表达式
        expression* tmp = new expression();  // 动态分配
        tmp->data = 0;
        tmp->isConst = false;
        tmp->isX = false;
        tmp->isExp = false;
        tmp->left = tmp->right = nullptr;
        tmp->op = NULL;
        
        //单一元素
        if (element[0] == 'x') {
            ll data = stoll(element.substr(1));
            tmp->data = data;
            tmp->isX = true;
            stk.push(tmp);
            all_expressions.push_back(tmp);
        }else if (element.size() == 1 && element[0] == '+') {
            expression* rightExp = stk.top();
            stk.pop();
            expression* leftExp = stk.top();
            stk.pop();
            tmp->op = '+';
            tmp->left = leftExp;
            tmp->right = rightExp;
            tmp->isExp = true;
            stk.push(tmp);
            all_expressions.push_back(tmp);
        }else if (element.size() == 1 && element[0] == '-') {
            expression* rightExp = stk.top();
            stk.pop();
            expression* leftExp = stk.top();
            stk.pop();
            tmp->op = '-';
            tmp->left = leftExp;
            tmp->right = rightExp;
            tmp->isExp = true;
            stk.push(tmp);
            all_expressions.push_back(tmp);
        }else if (element.size() == 1 && element[0] == '*') {
            expression* rightExp = stk.top();
            stk.pop();
            expression* leftExp = stk.top();
            stk.pop();
            tmp->op = '*';
            tmp->left = leftExp;
            tmp->right = rightExp;
            tmp->isExp = true;
            stk.push(tmp);
            all_expressions.push_back(tmp);
        }else {//整常数
            ll data = stoll(element);
            tmp->data = data;
            tmp->isConst = true;
            stk.push(tmp);
            all_expressions.push_back(tmp);
        }
    }
    expression* root = stk.top();
    for (int i = 0; i < m; ++i) {
        int x; cin >> x;
        for (int j = 1; j <= n; ++j) {
            ll data; cin >> data;
            a_list[j] = data;
        }
        ll res = daoExpression(*root,a_list,x);
        cout << modResult(res) << endl;
    }
    
    // // 释放内存
    // for (auto expr : all_expressions) {
    //     delete expr;
    // }
    
    return 0;
}