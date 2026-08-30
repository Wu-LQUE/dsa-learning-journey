#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll N,tdef,tmax,tmin,n; string H;
enum State {EMPTY,WAIT,OCUPY,EXPIRE};
struct IP {
    State st;
    string client;
    ll expireTime;
};
IP pool[10010];
unordered_map<string,set<ll>> client_ip;
set<ll> empIps;
set<ll> waitIps;
set<ll> exprIps;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t3.txt","r",stdin);
    cin >> N >> tdef >> tmax >> tmin >> H >> n;
    for (ll i = 1; i <= N; ++i) empIps.insert(i);
    while (n--) {
        ll t,ip,expr;string send,recv,type; cin >> t >> send >> recv >> type >> ip >> expr;
        if ((recv!=H)&&(recv!="*")&&(type!="REQ")) continue;
        if (type!="REQ"&&type!="DIS") continue;
        if ((recv=="*"&&type!="DIS")||(recv==H&&type=="DIS")) continue;

        //定时器处理
        for (auto it = waitIps.begin(); it != waitIps.end();) {
            if (pool[*it].expireTime<=t) {
                pool[*it].st=EMPTY;
                if (client_ip.count(pool[*it].client)) client_ip[pool[*it].client].erase(*it);
                pool[*it].client="";
                pool[*it].expireTime=0;
                empIps.insert(*it);
                it = waitIps.erase(it);
            }else {
                ++it;
            }
        }
        for (auto& cl : client_ip) {
            for (auto it = cl.second.begin(); it != cl.second.end(); ++it) {
                if (pool[*it].st==OCUPY&&pool[*it].expireTime<=t) {
                    pool[*it].st=EXPIRE;
                    // pool[*it].client=;
                    pool[*it].expireTime=0;
                    exprIps.insert(*it);
                    // it = cl.second.erase(it);
                }
            }
        }
        if (type=="DIS") {
            ll choseIp = 0;
            if (client_ip.count(send)&&!client_ip[send].empty()) choseIp = *client_ip[send].begin();
            else if (!empIps.empty()) { choseIp = *empIps.begin(); }  // 去掉这里的 erase
            else if (!exprIps.empty()) { choseIp = *exprIps.begin(); } // 去掉这里的 erase
            else continue;
            
            // --- 修复 3：统一清除选中 IP 的旧状态痕迹 ---
            string old_client = pool[choseIp].client;
            if (old_client != "" && old_client != send && client_ip.count(old_client)) {
                client_ip[old_client].erase(choseIp);
            }
            empIps.erase(choseIp);
            exprIps.erase(choseIp);
            waitIps.erase(choseIp); // 统统擦除，彻底防止同一个 IP 在两个集合里“幽灵”出现！

            pool[choseIp].st=WAIT; 
            pool[choseIp].client = send; 
            client_ip[send].insert(choseIp); 
            waitIps.insert(choseIp);
            
            ll exprTime;
            if (expr==0) exprTime = t + tdef;
            else {
                ll expect = expr - t;
                if (expect>tmax) expect = tmax;
                else if (expect<tmin) expect = tmin;
                exprTime = t + expect;
            }
            pool[choseIp].expireTime = exprTime;
            cout << H << " " << send << " " << "OFR" << " " << choseIp << " " << exprTime << '\n';
        }else if (type == "REQ") {
            if(recv!=H) {
                if (client_ip.count(send)&&!client_ip[send].empty()) {
                    for (auto p = client_ip[send].begin(); p != client_ip[send].end(); ) {
                        if (pool[*p].st==WAIT) {
                            pool[*p].st=EMPTY;
                            pool[*p].client="";
                            pool[*p].expireTime=0;
                            empIps.insert(*p);
                            waitIps.erase(*p);
                            p = client_ip[send].erase(p);
                        } else {
                            ++p;
                        }
                    }
                }
                continue;
            }
            if (1<=ip&&ip<=N&&pool[ip].client==send) {
                pool[ip].st=OCUPY;
                client_ip[send].insert(ip);
                exprIps.erase(ip);
                waitIps.erase(ip);
                ll exprTime;
                if (expr==0) exprTime = t + tdef;
                else {
                    ll expect = expr - t;
                    if (expect>tmax) expect = tmax;
                    else if (expect<tmin) expect = tmin;
                    exprTime = t + expect;
                }
                pool[ip].expireTime = exprTime;
                cout << H << " " << send << " " << "ACK" << " " << ip << " " << exprTime << '\n';
            }else {
                cout << H << " " << send << " " << "NAK" << " " << ip << " " << 0 << '\n';
            }
        }
    }
}