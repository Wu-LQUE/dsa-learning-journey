#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll n,N,q;
const int MAXN = 1e5+10;
struct cacheSet{
    list<pair<ll,bool>> cacheLine; //存了内存地址和dirty位
    unordered_map<ll,list<pair<ll,bool>>::iterator> posMap;
};
cacheSet cache[MAXN];
list<pair<ll,bool>>::iterator findInCacheSet(ll g,ll addr) {
    if (cache[g].posMap.count(addr)) return cache[g].posMap[addr];
    else return cache[g].cacheLine.end();
    // auto p = cache[g].cacheLine.begin();
    // for (;p != cache[g].cacheLine.end();++p) {
    //     if (p->first==addr) return p;
    // }
    // return p;
}
void put(ll group,ll addr,bool dirty) {
    auto& line = cache[group].cacheLine;
    if (line.size() < n) {
        line.push_front({addr,dirty});
        cache[group].posMap[addr] = line.begin();
    }else {
        auto& last = line.back();
        if (last.second) cout << '1' << ' ' << last.first << '\n';
        if (cache[group].posMap.count(last.first)) cache[group].posMap.erase(last.first);
        line.pop_back();
        line.push_front({addr,dirty});
        cache[group].posMap[addr] = line.begin();
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t3.txt","r",stdin);
    cin >> n >> N >> q;
    while (q--) {
        ll o,a; cin >> o >> a;
        ll group = (a / n) % N;
        auto& line = cache[group].cacheLine;
        list<pair<ll,bool>>::iterator p = findInCacheSet(group,a);
        if (o == 0) {
            if (p!=line.end()) {
                ll tmp_p_first = p->first;
                line.push_front({p->first,p->second});
                line.erase(p);
                cache[group].posMap[tmp_p_first] = line.begin();
            }else {
                put(group,a,false);
                cout << o << ' ' << a << '\n';
            }
        }else if (o == 1) {
            if (p!=line.end()) {
                ll tmp_p_first = p->first;
                line.push_front({p->first,true});
                line.erase(p);
                cache[group].posMap[tmp_p_first] = line.begin();
            }else {
                put(group,a,true);
                cout << '0' << ' ' << a << '\n';
            }
        }
    }
}