#include <bits/stdc++.h>
using namespace std;
const int N = 5,M = 9;
const int cspLogo[N][M] = {
    {1,1,1, 1,1,1, 1,1,1 },
    {1,0,0, 1,0,0, 1,0,1 },
    {1,0,0, 1,1,1, 1,1,0 },
    {1,0,0, 0,0,1, 1,0,0 },
    {1,1,1, 1,1,1, 1,0,0 },
};
int matrix[200][200];//n最大200
int kList[65536];//像素值在[0，65535]
int main() {
    freopen("logo.txt","r",stdin);
    vector<pair<int,int>> ones;
    vector<pair<int,int>> zeros;
    //预处理0/1的位置
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (cspLogo[i][j]==1) {
                ones.push_back({i,j});
            }else {
                zeros.push_back({i,j});
            }
        }
    }
    int n,L; cin >> n >> L;
    //读入图像矩阵
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }
    //枚举所有csp位置
    for (int i = 0; i <= n-5; ++i) {
        for (int j = 0; j <= n-9; ++j) {
            int min1=INT_MAX,max0=-1;//1找最小k值，0找最大k值
            for (auto [dx,dy] : ones) {
                int k1 = matrix[i+dx][j+dy];
                min1 = min(k1,min1);
            }
            for (auto [dx,dy] : zeros) {
                int k0 = matrix[i+dx][j+dy]+1;
                max0 = max(k0,max0);
            }
            // int a = 1;
            //[max0,min1]区间+1
            if (max0 <= min1) {
                // cout << (max0 >= min1) << endl;
                // cout << min1 << "," << max0 << endl;
                kList[max0]++;
                if (min1 < 65535) {
                    kList[min1+1]--;
                }
            }
        }
    }
    //前缀和
    for (int i = 0; i < 65536; ++i) {
        if (i >= 1 ) {
            kList[i]+=kList[i-1];
        }
        if (kList[i]>0) {
            cout << i << endl;
        }
    }
}

// vector<vector<int>> cspLogo;

// vector<int> hasLogo(const vector<vector<int>> &matrix,int i,int j,int L) {
//     vector<int> kList;
    
//     for(int k = 0;k <= matrix[i][j] && k <= L - 1;++k) {
//         //做pattern匹配
//         for (int i2 = i; i2 <= i+4; ++i2) {
//             for (int j2 = j; j2 <= j+8; ++j2) {
//                 int val = matrix[i2][j2] >= k ? 1 : 0;
//                 if (val != cspLogo[i2-i][j2-j]) goto breakLable;
//             }
//         }
//         kList.push_back(k);
//         breakLable:
//             continue;
//     }
//     return kList;
// }

// int main() {
//     freopen("logo.txt","r",stdin);
//     vector<int> cspLogoLine (9);
//     cspLogoLine = {1,1,1, 1,1,1, 1,1,1 };
//     cspLogo.push_back(cspLogoLine);
//     cspLogoLine = {1,0,0, 1,0,0, 1,0,1 };
//     cspLogo.push_back(cspLogoLine);
//     cspLogoLine = {1,0,0, 1,1,1, 1,1,0 };
//     cspLogo.push_back(cspLogoLine);
//     cspLogoLine = {1,0,0, 0,0,1, 1,0,0 };
//     cspLogo.push_back(cspLogoLine);
//     cspLogoLine = {1,1,1, 1,1,1, 1,0,0 };
//     cspLogo.push_back(cspLogoLine);
//     int n,L;
//     cin >> n; cin >> L;
//     vector<vector<int>> matrix;
//     for (int i = 0; i < n; ++i) {
//         vector<int> row(n);
//         for (int j = 0 ; j < n; ++j) {
//             cin >> row[j];
//         }
//         matrix.push_back(row);
//     }
//     //水印计算：穷尽所有5*9
//     set<int> kList;
//     // int iSkip = 0, jSkip = 0;
//     for (int i = 0; i <= n-5; ++i) {
//         // if (iSkip!=0) {
//         //     i+=iSkip;
//         //     iSkip = 0;
//         //     jSkip = 0;
//         //     if (i > n-5) break;
//         // }
//         for (int j = 0; j <= n-9; ++j) {
//             // if (jSkip!=0) {
//             //     j+=jSkip;
//             //     jSkip = 0;
//             //     if (j > n-9) break;
//             // }
//             // cout << i << " " << j << endl;
//             vector<int> ks = hasLogo(matrix,i,j,L);
//             for (auto p = ks.begin();p!=ks.end();++p) {
//                 kList.insert(*p);
//             }
//             // if (ks.size()>0) {
//             //     iSkip = 3;
//             //     jSkip = 8;
//             // }
//         }
//     }
//     for (auto p = kList.begin();p!=kList.end();++p) {
//         cout << *p << endl;
//     }
// }