#include <bits/stdc++.h>
using namespace std;

/* 回溯算法：子集和 I */
void backtrack(vector<int> &state, int target, int total, vector<int> &choices, vector<vector<int>> &res) {
    if (total == target) {
        res.push_back(state);
        return;
    }
    for (int i = 0; i < choices.size(); ++i) {
        int choice = choices[i];
        if (total + choice > total) {
            continue;
        }else {
            state.push_back(choice);
            backtrack(state,target,total + choice,choices,res);
            state.pop_back();
        }
    }
}

/* 求解子集和 I（包含重复子集） */
vector<vector<int>> subsetSumINaive(vector<int> &nums, int target) {
    vector<int> state;       // 状态（子集）
    int total = 0;           // 子集和
    vector<vector<int>> res; // 结果列表（子集列表）
    backtrack(state, target, total, nums, res);
    return res;
}