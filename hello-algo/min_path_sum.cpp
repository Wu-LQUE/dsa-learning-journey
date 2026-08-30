#include <bits/stdc++.h>
using namespace std;

//动态规划：构造首行和首列，状态转移方程计算
int minPathSumDP(vector<vector<int>> &grid) {
    int n = grid.size(),m = grid[0].size();
    vector<vector<int>> dp(n,vector<int> (m));
    dp[0][0] = grid[0][0];
    //首行
    for (int i = 1; i < m; ++i) {
        dp[0][i] = dp[0][i-1] + grid[0][i];
    }
    //首列
    for (int i = 1; i < n; ++i) {
        dp[i][0] = dp[i-1][0] + grid[i][0];
    }
    //其余
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            dp[i][j] = min(dp[i-1][j],dp[i][j-1]) + grid[i][j];
        }
    }
    return dp[n-1][n-1];
}

//做一个空间优化
int minPathSumDPMemRefine(vector<vector<int>> &grid) {
    int n = grid.size(),m = grid[0].size();
    vector<int> dp(m);
    dp[0] = grid[0][0];
    //首行
    for (int i = 1; i < m; ++i) {
        dp[i] = dp[i-1] + grid[0][i];
    }
    //其余
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j == 0) {
                //首列
                dp[0] = dp[0] + grid[i][0];
            }else {
                dp[j] = min(dp[j-1],dp[j]) + grid[i][j];
            }
        }
    }
    return dp[m-1];
}

int calMinPathSumDP() {
    vector<vector<int>> grid;
    grid = {
        {1,3,1,5},
        {2,2,4,2},
        {5,3,2,1},
        {4,3,5,2}
    };
    return minPathSumDP(grid);
}

int calMinPathSumDPMemRefine() {
    vector<vector<int>> grid;
    grid = {
        {1,3,1,5},
        {2,2,4,2},
        {5,3,2,1},
        {4,3,5,2}
    };
    return minPathSumDPMemRefine(grid);
}

//当然可以使用dfs加记忆，时间复杂度也是O(nm)
/* 最小路径和：记忆化搜索 */
int minPathSumDFSMem(vector<vector<int>> &grid, vector<vector<int>> &mem, int i, int j) {
    if (i == 0 && j == 0) return grid[0][0];
    if (i < 0 || j < 0) return INT_MAX;//越界了取最大值
    int up = minPathSumDFSMem(grid,mem,i-1,j);
    int left = minPathSumDFSMem(grid,mem,i,j-1);
    mem[i][j] = min(up,left) != INT_MAX ? min(up,left) + grid[i][j] : INT_MAX;
    return mem[i][j];
}

int calMinPathSumDFS() {
    vector<vector<int>> grid;
    grid = {
        {1,3,1,5},
        {2,2,4,2},
        {5,3,2,1},
        {4,3,5,2}
    };
    vector<vector<int>> mem (grid.size(),vector<int> (grid[0].size()));
    return minPathSumDFSMem(grid,mem,grid.size()-1,grid[0].size()-1);
}


int main() {
    cout << calMinPathSumDP() << endl;
    cout << calMinPathSumDFS() << endl;
    cout << calMinPathSumDPMemRefine() << endl;
}