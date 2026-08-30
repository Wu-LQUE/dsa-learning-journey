#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 505;
ll n,m,q;
struct character {
    string name;
    ll nv;
    unordered_set<string> opList;//操作
    ll no;
    unordered_set<string> resType;//资源种类
    ll nn;
    unordered_set<string> resName;//资源名称
};
struct lk {
    string charName;
    ll ns;
    vector<pair<string,string>> pairs;//ns对，u/g->name
};
struct action {
    string userName;
    ll ng;
    vector<string> userGroup;
    string opName;
    string resType;
    string resName;
};
character chars[N];
lk links[N];
// 倒排索引做优化！
// 角色名称 -> 角色id(1-n)
unordered_map<string,int> role_name_to_id;
unordered_map<string,vector<int>> user_to_roles;
unordered_map<string,vector<int>> group_to_roles;

bool check(const action &act) {
    bool has_role[N] = {false};
    if (user_to_roles.count(act.userName)) {
        for (int r_id : user_to_roles[act.userName]) has_role[r_id] = true;
    }
    for (const auto& g : act.userGroup) {
        if (group_to_roles.count(g)) {
            for (int r_id : group_to_roles[g]) has_role[r_id] = true;
        }
    }
    ll flag = false;
    for (int r_id = 1; r_id <= n; ++r_id) {
        if (!has_role[r_id]) continue;
        const auto& ch = chars[r_id];
        if (flag) break;
        if (!ch.opList.count(act.opName)&&!ch.opList.count("*")) continue;
        if (!ch.resType.count(act.resType)&&!ch.resType.count("*")) continue;
        if (!ch.resName.count(act.resName)&&ch.nn!=0) continue;
        flag = true;
        break;
    }
    return flag;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t3.txt","r",stdin);
    cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i) {
        
        cin >> chars[i].name >> chars[i].nv; chars[i].opList.reserve(chars[i].nv+1);
        for (int j = 1; j <= chars[i].nv; ++j) {string tmp; cin >> tmp; chars[i].opList.insert(tmp);}
        role_name_to_id[chars[i].name]=i;
        
        cin >> chars[i].no; chars[i].resType.reserve(chars[i].no+1);
        for (int j = 1; j <= chars[i].no; ++j) {string tmp; cin >> tmp; chars[i].resType.insert(tmp);}
        cin >> chars[i].nn; chars[i].resName.reserve(chars[i].nn+1);
        for (int j = 1; j <= chars[i].nn; ++j) {string tmp; cin >> tmp; chars[i].resName.insert(tmp);}
    }
    for (int i = 1; i <= m; ++i) {
        cin >> links[i].charName >> links[i].ns; links[i].pairs.reserve(links[i].ns);
        int role_id = role_name_to_id.count(links[i].charName) ? role_name_to_id[links[i].charName] : 0;
        for (int j = 1; j <= links[i].ns; ++j) {
            string type,name; cin >> type >> name;
            links[i].pairs.push_back({type,name});
            if (type == "u") {
                user_to_roles[name].push_back(role_id);
            }else if (type == "g") {
                group_to_roles[name].push_back(role_id);
            }
        }
    }

    for (int i = 1; i <= q; ++i) {
        action act;
        cin >> act.userName >> act.ng; act.userGroup.reserve(act.ng+1);
        for (int j = 1; j <= act.ng; ++j) {string tmp; cin >> tmp; act.userGroup.push_back(tmp);}
        cin >> act.opName >> act.resType >> act.resName;
        cout << check(act) << '\n';
    }
}