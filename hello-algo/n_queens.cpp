#include <bits/stdc++.h>
using namespace std;
/* 回溯算法：n 皇后 */
void backtrack(vector<vector<string>> state,vector<vector<vector<string>>> &res,int n,int row,vector<bool> &cols,vector<bool> &diags1, vector<bool> &diags2) {
    if (row == n) {
        res.push_back(state);
        return;
    }
    //遍历这一行的所有列，尝试放置
    for (int col = 0; col < n; ++col) {
        int diag1 = row - col + n - 1;//加上n-1将主对角线映射到[0,2n-2]
        int diag2 = row + col;//[次对角线不需要]
        if (cols[col] == false && diags1[diag1] == false && diags2[diag2] == false) {
            state[row][col] = "Q";
            cols[col] = true;
            diags1[diag1] = true;
            diags2[diag2] = true;
            backtrack(state,res,n,row+1,cols,diags1,diags2);
            state[row][col] = "#";
            cols[col] = diags1[diag1] = diags2[diag2] = false;
        }
    }
}

vector<vector<vector<string>>> nQueens(int n) {
    vector<vector<string>> state (n,vector<string> (n,"#"));
    vector<vector<vector<string>>> result;
    vector<bool> cols (n);
    //主次对角线
    vector<bool> diags1 (2*n-1,false);
    vector<bool> diags2 (2*n-1,false);
    backtrack(state,result,n,0,cols,diags1,diags2);
    return result;
}

int main() {
    vector<vector<vector<string>>> res;
    res = nQueens(8);
    for (int r = 0; r < res.size(); ++r) {
        vector<vector<string>> board = res[r];
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size();++j) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}