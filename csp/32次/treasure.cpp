#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long

struct Matrix {
    ull data[2][2];
};

void readInsCin(string &ins) {
    getline(cin, ins); 
}

void readInsSS(stringstream &ss, string &ins) {
    getline(ss, ins); 
}

void execIns(vector<string> &insArr, deque<Matrix> &mats, int l, int r) {
    mats.clear();
    int lastInsert = -1; // 0为front，1为back
    stack<int> latestInsert;
    for (int i = l; i <= r; ++i) {
        string ins = insArr[i];
        stringstream ss(ins);
        int v; ss >> v;
        
        switch (v) {
        case 1: {
            Matrix mat;
            ss >> mat.data[0][0] >> mat.data[0][1] >> mat.data[1][0] >> mat.data[1][1];
            mats.push_front(mat);
            lastInsert = 0;
            latestInsert.push(lastInsert);
            break;
        }
        case 2: {
            Matrix mat;
            ss >> mat.data[0][0] >> mat.data[0][1] >> mat.data[1][0] >> mat.data[1][1];
            mats.push_back(mat);
            lastInsert = 1;
            latestInsert.push(lastInsert);
            break;
        }
        case 3: {
            if (mats.empty()) break;
            lastInsert = latestInsert.top();
            latestInsert.pop();
            if (lastInsert == 1) { // 1为back
                mats.pop_back();
            } else if (lastInsert == 0) { // 0为front
                mats.pop_front();
            }
            break;
        }
        default:
            break;
        }
    }
    
    // 队列矩阵相乘
    if (mats.empty()) {
        cout << "1 0 0 1" << endl;
        return;
    }
    
    Matrix resMat = mats.front();
    
    // 处理矩阵乘积
    for (auto it = mats.begin() + 1; it != mats.end(); ++it) {
        Matrix tmpMat = *it;
        ull a00 = resMat.data[0][0] * tmpMat.data[0][0] + resMat.data[0][1] * tmpMat.data[1][0];
        ull a01 = resMat.data[0][0] * tmpMat.data[0][1] + resMat.data[0][1] * tmpMat.data[1][1];
        ull a10 = resMat.data[1][0] * tmpMat.data[0][0] + resMat.data[1][1] * tmpMat.data[1][0];
        ull a11 = resMat.data[1][0] * tmpMat.data[0][1] + resMat.data[1][1] * tmpMat.data[1][1];
        resMat.data[0][0] = a00;
        resMat.data[0][1] = a01;
        resMat.data[1][0] = a10;
        resMat.data[1][1] = a11;

        ull modNum = 998244353;
        resMat.data[0][0] %= modNum;
        resMat.data[0][1] %= modNum;
        resMat.data[1][0] %= modNum;
        resMat.data[1][1] %= modNum;
    }
    
    
    cout << resMat.data[0][0] << " " << resMat.data[0][1] << " " 
         << resMat.data[1][0] << " " << resMat.data[1][1] << endl;
}

int main() {
    freopen("treasure.txt", "r", stdin);
    int n, m; 
    cin >> n >> m;
    cin.ignore(); // 忽略换行符，否则n,m后用getline直接读到\n
    
    vector<string> instructions(n + 1);
    deque<Matrix> matrixQueue;
    
    // 读初始n条
    for (int i = 1; i <= n; ++i) {
        string ins; 
        readInsCin(ins);
        instructions[i] = ins;
    }
    
    // m个时刻的事件
    for (int i = 1; i <= m; ++i) {
        string ins; 
        readInsCin(ins);
        stringstream ss(ins);
        
        // 解析ins
        int v; ss >> v;
        switch (v) {
        case 1: {
            int pos; ss >> pos;
            string remaining;
            readInsSS(ss, remaining);
            instructions[pos] = remaining;
            break;
        }
        case 2: {
            int l, r; ss >> l >> r;
            execIns(instructions, matrixQueue, l, r);
            break;
        }
        default:
            break;
        }
    }
    
    return 0;
}