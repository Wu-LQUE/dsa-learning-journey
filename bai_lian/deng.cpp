#include <iostream>
#include <bitset>
#include <vector>
using namespace std;

const int ROWS = 5;
const int COLS = 6;
const int TOTAL = ROWS * COLS;

class LightsOutSolver {
private:
    vector<vector<int>> board;  // 当前灯的状态
    vector<vector<int>> presses; // 记录按下的位置
    vector<vector<int>> initial; // 初始状态
    
    // 按下(r,c)位置的灯
    void press(int r, int c) {
        presses[r][c] = 1;
        
        // 翻转自己和周围灯的状态
        board[r][c] ^= 1;
        if (r > 0) board[r-1][c] ^= 1;
        if (r < ROWS-1) board[r+1][c] ^= 1;
        if (c > 0) board[r][c-1] ^= 1;
        if (c < COLS-1) board[r][c+1] ^= 1;
    }
    
    // 尝试一种第一行的按法
    bool tryFirstRow(int firstRowPattern) {
        // 重置状态
        board = initial;
        presses = vector<vector<int>>(ROWS, vector<int>(COLS, 0));
        
        // 根据第一行的按法按下按钮
        for (int c = 0; c < COLS; c++) {
            if (firstRowPattern & (1 << c)) {
                press(0, c);
            }
        }
        
        // 从第二行开始，根据上一行的状态确定是否按下
        for (int r = 1; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                // 如果上一行的灯还亮着，必须按这个位置的灯来关掉它
                if (board[r-1][c] == 1) {
                    press(r, c);
                }
            }
        }
        
        // 检查最后一行是否全灭
        for (int c = 0; c < COLS; c++) {
            if (board[ROWS-1][c] == 1) {
                return false;
            }
        }
        
        return true;
    }

public:
    LightsOutSolver(const vector<vector<int>>& init) : initial(init) {}
    
    vector<vector<int>> solve() {
        // 枚举第一行的所有按法（2^COLS = 64种）
        for (int pattern = 0; pattern < (1 << COLS); pattern++) {
            if (tryFirstRow(pattern)) {
                return presses;  // 找到解
            }
        }
        
        return vector<vector<int>>();  // 无解（理论上不会发生）
    }
};

int main() {
    vector<vector<int>> randomInitial(5,vector<int> (6));
    for (int i = 0; i < 5; ++i){
        for (int j = 0; j < 6; ++j) cin >> randomInitial[i][j];
    }
    LightsOutSolver solver2(randomInitial);
    vector<vector<int>> solution2 = solver2.solve();
    for (int i = 0; i < 5; ++i){
        for (int j = 0; j < 6; ++j) cout << solution2[i][j] << " ";
        cout << endl;
    }
    return 0;
}