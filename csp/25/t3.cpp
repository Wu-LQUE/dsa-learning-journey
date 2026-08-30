#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 1e3+10;
ll n,m,g;
set<ll> avZone[N];//记录zone对应node
int node2zone[N];
map<ll,set<ll>> app2zone;
map<ll,set<ll>> app2node;
map<ll,ll> node2tasks;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t3.txt","r",stdin);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        ll l; cin >> l;
        avZone[l].insert(i);
        node2zone[i] = l;
    }
    cin >> g;
    for (int i = 1; i <= g; ++i) {
        ll f,a,na,pa,paa,paar;
        cin >> f >> a >> na >> pa >> paa >> paar;
        for (int j = 1; j <= f; ++j) {
            set<ll> zoneList; bool flag = true;
            set<ll> avNode;
            set<ll> disNode;
            vector<pair<ll,ll>> node_tasks;
            if (pa) {
                if (!app2zone.count(pa)) {
                    flag = false;
                    goto end;
                }else {
                    zoneList = app2zone[pa];
                    if (!na) {}
                    else if (!zoneList.count(na)) {
                        flag = false;
                        goto end;
                    }else {
                        zoneList.clear();
                        zoneList.insert(na);
                    }
                }
            } else {
                if (na) zoneList.insert(na);
                else for (int k = 1; k <= m; ++k) zoneList.insert(k);
                
            }
            for (const auto& zone : zoneList) {
                avNode.insert(avZone[zone].begin(),avZone[zone].end());
            }
            if (paa) {
                disNode = app2node[paa];
            }
            for (const auto& node : avNode) {
                node_tasks.push_back({node,node2tasks[node]});
            }
            sort (node_tasks.begin(),node_tasks.end(),[](const pair<ll,ll>& a,const pair<ll,ll>& b){
                if (a.second != b.second) {
                    return a.second < b.second;
                }else {
                    return a.first < b.first;
                }
            });
            end:
            if (!flag) {
                cout << 0 << ' ';
            }else {
                flag = false;
                if (paa) {
                    if (paar) {
                        for (const auto& p : node_tasks) {
                            if (!disNode.count(p.first)) {
                                cout << p.first << ' ';
                                app2zone[a].insert(node2zone[p.first]);
                                app2node[a].insert(p.first);
                                node2tasks[p.first]++;
                                flag = true;
                                break;
                            }
                        }
                    }else {
                        for (const auto& p : node_tasks) {
                            if (!disNode.count(p.first)) {
                                cout << p.first << ' '; 
                                app2zone[a].insert(node2zone[p.first]);
                                app2node[a].insert(p.first);
                                node2tasks[p.first]++;
                                flag = true;
                                break;
                            }
                        }
                        if (!flag && !node_tasks.empty()) {
                            cout << node_tasks[0].first << ' ';
                            app2zone[a].insert(node2zone[node_tasks[0].first]);
                            app2node[a].insert(node_tasks[0].first);
                            node2tasks[node_tasks[0].first]++;
                            flag = true;
                        }
                    }
                }else {
                    if (!node_tasks.empty()) {
                        cout << node_tasks[0].first << ' ';
                        app2zone[a].insert(node2zone[node_tasks[0].first]);
                        app2node[a].insert(node_tasks[0].first);
                        node2tasks[node_tasks[0].first]++;
                        flag = true;
                    }
                }
                if (!flag) cout << 0 << ' ';
            }
        }
        cout << '\n';
    }
}