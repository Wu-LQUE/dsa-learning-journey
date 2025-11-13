#include <bits/stdc++.h>
using namespace std;

//做引用传递以减少内存浪费
void backtrack(vector<int> &state, const vector<int> &choices, vector<bool> &selected, vector<vector<int>> &res) {
    if (state.size() == choices.size()) {
        res.push_back(state);
        return;
    }
    for (int i = 0; i < choices.size(); ++i) {
        int choice = choices[i];
        // 剪枝
        if (!selected[i]) {
            //做出尝试，修改状态
            selected[i] = true;
            state.push_back(choice);
            //深度搜索
            backtrack(state,choices,selected,res);
            //恢复状态
            selected[i] = false;
            state.pop_back();
        }
    }
}
//全排列
vector<vector<int>> permutations(vector<int> nums) {
    vector<int> state;
    vector<bool> selected(nums.size(),false);
    vector<vector<int>> res;
    backtrack(state,nums,selected,res);
    return res;
}

int main() {
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);
    vector<vector<int>> result = permutations(nums);
    return 0;
}