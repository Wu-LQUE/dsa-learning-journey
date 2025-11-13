#include <bits/stdc++.h>
using namespace std;

/* 回溯算法：全排列 II */
void backtrack(vector<int> &state, const vector<int> &choices, vector<bool> &selected, vector<vector<int>> &res) {
    // 当状态长度等于元素数量时，记录解
    if (state.size() == choices.size()) {
        res.push_back(state);
        return;
    }
    //记录该轮中已经尝试过的元素，并将重复元素剪枝
    unordered_set<int> duplicated;
    for (int i = 0; i < choices.size(); ++i) {
        int choice = choices[i];
        //choices未选过的，不相等的
        if (!selected[i] && duplicated.find(choice) == duplicated.end()) {
            // 尝试：做出选择，更新状态
            duplicated.emplace(choice);// 记录选择过的元素值
            selected[i] = true;
            state.push_back(choice);
            backtrack(state,choices,selected,res);
            selected[i] = false;
            state.pop_back();
        }
    }
}
/* 全排列 II */
vector<vector<int>> permutationsII(vector<int> nums) {
    vector<int> state;
    vector<bool> selected(nums.size(), false);
    vector<vector<int>> res;
    backtrack(state, nums, selected, res);
    return res;
}
int main() {
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(1);
    nums.push_back(3);
    vector<vector<int>> result = permutationsII(nums);
    return 0;
}