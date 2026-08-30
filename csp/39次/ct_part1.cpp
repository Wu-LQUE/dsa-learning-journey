#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    vector<TreeNode*> children;
    TreeNode *parent;
    int data;
    bool isVisited;
};

void dfs(TreeNode *endNode,TreeNode *curNode,vector<int> &record,vector<vector<int>> &result) {
    if (curNode == endNode) {
        result.push_back(record);
        return;
    }
    TreeNode *parent = curNode->parent;
    if (parent && !parent->isVisited) {
        parent->isVisited = true;
        record.push_back(parent->data);
        dfs(endNode,parent,record,result);
        record.pop_back();
        parent->isVisited = false;
    }
    vector<TreeNode*> children = curNode->children;
    for (int i = 0; i < children.size();++i) {
        if (!children[i]->isVisited) {
            children[i]->isVisited = true;
            record.push_back(children[i]->data);
            dfs(endNode,children[i],record,result);
            record.pop_back();
            children[i]->isVisited = false;
        }
    }

}

int getMex(vector<TreeNode> &nodes,int start,int end) {
    TreeNode* targetNode = &nodes[end];
    TreeNode* startNode = &nodes[start];
    startNode->isVisited = true;
    vector<int> record;
    vector<vector<int>> res;
    record.push_back(startNode->data);
    dfs(targetNode,startNode,record,res);
    sort(res[0].begin(),res[0].end());
    int mex = 0;
    while (mex < res[0].size() && mex == res[0][mex]) {
        ++mex;
    }
    return mex;
}

int main() {
    freopen("ct_part1.txt","r",stdin);
    int nodeNum,ruleNum;
    cin >> nodeNum; cin >> ruleNum;
    vector<TreeNode> nodes(nodeNum+1);
    for (int i = 1; i <= nodeNum; ++i) {
        TreeNode node;
        cin >> node.data;
        node.parent = NULL;
        nodes[i]=node;//做拷贝，当然可以用new
    }
    //建边
    for (int i = 0; i < nodeNum-1; ++i) {
        int parent,child;
        cin >> parent; cin >> child;
        nodes[parent].children.push_back(&nodes[child]);
        nodes[child].parent = &nodes[parent];
    }
    //暴力求mex
    for (int i = 0; i < ruleNum; ++i) {
        int start,end;
        cin >> start; cin >> end;
        for (int i = 1; i <= nodeNum; ++i) {
            nodes[i].isVisited = false;
        }
        cout << getMex(nodes,start,end) << endl;
    }
    return 0;
}