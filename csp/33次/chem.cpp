#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void swapRow(vector<vector<double>> &matrix,int r1,int r2,int startColumn) {
    vector<double> tmp = matrix[r1];
    for (int j = startColumn; j < tmp.size(); ++j) {
        matrix[r1][j] = matrix[r2][j];
        matrix[r2][j] = tmp[j];
    }
}
const double EPS = 1e-10;
bool isZero(double x) {
    return std::fabs(x) < EPS;
}
int main() {
    freopen("chem.txt","r",stdin);
    int equalNum;
    cin >> equalNum;
    //处理每个方程
    for (int i = 0; i < equalNum; ++i) {
        int materialNum;
        cin >> materialNum;//物质数
        //系数数组，数组每条是一个map，key是元素名，val是元素的系数数组
        map<string,vector<double>> xiShuMatrix;
        //读每个物质
        for (int j = 0; j < materialNum; ++j) {
            char material[400];
            cin >> material;
            //物质的读取
            int read_pos = 0;
            int readChars;
            char yuanSu[100];
            int yuanSuXishu;
            //读物质的每个元素
            while (sscanf(material+read_pos,"%[^0-9]%d%n",yuanSu,&yuanSuXishu,&readChars)==2) {
                string key(yuanSu);
                if (xiShuMatrix.find(key)==xiShuMatrix.end()) {
                    //创建这个元素对应的数组
                    xiShuMatrix[key] = vector<double> (materialNum,0);
                }
                //往元素对应列写入系数
                xiShuMatrix[key][j] = yuanSuXishu;
                read_pos+=readChars;
            }
        }
        //行,列
        int row = xiShuMatrix.size(),col = materialNum;
        //转为数字矩阵
        vector<vector<double>> matrix;
        for (auto p = xiShuMatrix.begin();p !=xiShuMatrix.end();++p) {
            matrix.push_back(p->second);
        }
        //高斯消元
        //遍历每一列
        int currentRow = 0;
        for (int j = 0;j < col && currentRow < row; ++j) {
            //列首为0，可能交换,全0不交换
            if (isZero(matrix[currentRow][j])) {
                matrix[currentRow][j] = 0;
                //是否交换了
                int exchanged = 0;
                for (int i = currentRow; i < row; ++i) {
                    if (!isZero(matrix[i][j])) {
                        swapRow(matrix,currentRow,i,j);
                        exchanged = 1;
                        break;
                    }
                }
                //第一列全0，直接下一列
                if (exchanged==0) {
                    continue;
                }
            }
            //列首不为0了，后面所有行都消去
            for (int i = currentRow+1; i < row; ++i) {
                double k = -matrix[i][j]/matrix[currentRow][j];
                for (int j2 = j; j2 < col; ++j2) {
                    matrix[i][j2]+=matrix[currentRow][j2]*k;
                }
            }
            ++currentRow;
        }
        //计算rank:统计非0行数目
        int rank = 0;
        for (int i = 0; i < row; ++i) {
            int isAllZero = 1;
            //该行所有元素
            for (int j2 = 0; j2 < col; ++j2) {
                if (isZero(matrix[i][j2])!=1) {
                    isAllZero = 0;
                    break;
                }
            }
            if (!isAllZero) {
                rank++;
            }
        }
        //是否有解
        int solve = materialNum - rank;
        if (solve > 0) {
            cout << "Y" << endl;
        }else {
            cout << "N" << endl;
        }
    }
}