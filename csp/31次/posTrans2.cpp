#include <bits/stdc++.h>
using namespace std;
#define ll long long
// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(nullptr);
//     freopen("posTrans2.txt","r",stdin);
//     int n,m; cin >> n >> m;
//     cin.ignore();
//     vector<string> ops(n);
//     for (int i = 0; i < n; ++i) {
//         string op;
//         getline(cin,op);
//         ops[i] = op;
//     }
//     for (int t = 0; t < m; ++t) {
//         int i,j; cin >> i >> j;
//         double x,y; cin >> x >> y;
//         //执行运算
//         for(; i <= j; ++i) {
//             stringstream ss(ops[i-1]);
//             int opcode;
//             ss >> opcode;
//             double arg;
//             ss >> arg;
//             switch (opcode)
//             {
//             case 1:
//                 x *= arg;
//                 y *= arg;
//                 break;
//             case 2:{
//                 double tmpX, tmpY;
//                 tmpX = x * cos(arg) - y * sin(arg);
//                 tmpY = x * sin(arg) + y * cos(arg);
//                 x = tmpX;
//                 y = tmpY;
//                 break;
//             }
//             default:
//                 break;
//             }
//         }
//         // printf("%.3f %.3f\n",x,y);
//         cout << fixed << setprecision(3) << x << " " << y << "\n";
//     }
// }
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("posTrans2.txt","r",stdin);
    int n,m; cin >> n >> m;
    cin.ignore();
    vector<double> k(n+1,1);
    vector<double> angle(n+1);
    for (int i = 1; i <= n; ++i) {
        int op; cin >> op;
        double arg; cin >> arg;
        if (op == 1) {
            k[i] = k[i-1] * arg;
            angle[i] = angle[i-1];
        }else {
            angle[i] = angle[i-1] + arg;
            k[i] = k[i-1];
        }
    }
    //m个
    for (int t = 0; t < m; ++t) {
        int i,j; cin >> i >> j;
        double x,y; cin >> x >> y;
        double kVal = k[j] / k[i-1];
        double aVal = angle[j] - angle[i-1];
        
        double new_x = x * cos(aVal) - y * sin(aVal);
        double new_y = x * sin(aVal) + y * cos(aVal);
        new_x *= kVal;
        new_y *= kVal;
        
        cout << fixed << setprecision(3) << new_x << ' ' << new_y << '\n';
    }
}