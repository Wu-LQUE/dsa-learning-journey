#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll totalWeight;
const int MAX_N = 2000 + 5;
int isDeleted[MAX_N];
struct TreeNode{
    vector<TreeNode*> children;
    TreeNode *parent;
    int nodeNumber;
    ll weight;
    ll subWeight;
    ll subWeightBackup;
};
TreeNode *root;
int isHoudai(vector<TreeNode> &nodes,int nodeParentIdx,int nodeChildIdx) {
    if (nodeChildIdx==nodeParentIdx) return 1;
    TreeNode *nodeParent=&nodes[nodeParentIdx],*nodeChild=&nodes[nodeChildIdx];
    int isHou = 0;
    while (nodeChild->parent!=NULL) {
        if (nodeChild->parent == nodeParent) {
            isHou = 1;
            break;
        }else {
            nodeChild = nodeChild->parent;
        }
    }
    return isHou;
}

void labelDeleted(TreeNode *node) {
    isDeleted[node->nodeNumber]=1;
    for (int i = 0; i < node->children.size(); ++i) {
        labelDeleted(node->children[i]);
    }
}


void query(vector<TreeNode> &nodes,int number){
    while (true)
    {
        //选出最小node
        // queue<TreeNode*> q;
        // q.push(root);
        int minNodeIdx=0;
        ll minData=LONG_LONG_MAX;
        // while (q.size()) {
        //     TreeNode *node = q.front();
        //     q.pop();
        //     ll absWeight = abs(node->subWeight - (totalWeight - node->subWeight));
        //     if (absWeight < minData) {
        //         minData = absWeight;
        //         minNodeIdx = node->nodeNumber;
        //     }
        //     //遍历子树
        //     for (int i = 0; i < node->children.size(); ++i) {
        //         if (isDeleted[node->children[i]->nodeNumber]==1) {
        //             continue;
        //         }else {
        //             q.push(node->children[i]);
        //         }
        //     }
        // }
        for (int i = 1; i <= nodes.size()-1; ++i) {
            TreeNode *tmpNode = &nodes[i];
            if (isDeleted[tmpNode->nodeNumber]==1) continue;
            ll absWeight = abs(tmpNode->subWeight - (totalWeight - tmpNode->subWeight));
            if (absWeight < minData) {
                minData = absWeight;
                minNodeIdx = tmpNode->nodeNumber;
            }
        }
        cout << minNodeIdx << " ";
        //询问是否被包含
        if (isHoudai(nodes,minNodeIdx,number)) {
            root = &nodes[minNodeIdx];
            for (int i = 1; i <= nodes.size(); ++i) {
                TreeNode *tmpNode = &nodes[i];
                if (isDeleted[tmpNode->nodeNumber]==1) continue;
                if (isHoudai(nodes,minNodeIdx,tmpNode->nodeNumber)) continue;
                isDeleted[tmpNode->nodeNumber] = 1;
            }
            totalWeight = nodes[minNodeIdx].subWeight;
        }else {
            //删除这棵子树
            // isDeleted[minNodeIdx] = 1;
            labelDeleted(&nodes[minNodeIdx]);
            TreeNode *nodeChild = &nodes[minNodeIdx];
            ll delWeight = nodeChild->subWeight;
            totalWeight -= delWeight;
            // int isDel = 0;
            while (nodeChild->parent!=NULL) {
                TreeNode *nodeParent = nodeChild->parent;
                nodeParent->subWeight -= delWeight;
                nodeChild = nodeChild->parent;
            }
        }
        int rootChildren = 0;
        for (int i = 0; i < root->children.size(); ++i) {
            if (!isDeleted[root->children[i]->nodeNumber]) rootChildren++;
        }
        if (root==&nodes[number] && rootChildren==0) {
            break;
        }
    }
    cout << endl;
}

ll sumWeight(TreeNode *node){
    if (node->children.size()==0) {
        node->subWeight = node->weight;
        node->subWeightBackup = node->subWeight;
        return node->subWeight;
    }else {
        ll total = 0;
        for (int i = 0; i < node->children.size(); ++i) {
            total += sumWeight(node->children[i]);
        }
        node->subWeight = total + node->weight;
        node->subWeightBackup = node->subWeight;
        return node->subWeight;
    }
}

int main(){
    freopen("tree.txt","r",stdin);
    int n,m; cin >> n >> m;
    vector<TreeNode> nodes (n+1);

    //建树
    for (int i = 1; i <= n; ++i) {
        TreeNode tmp;
        cin >> tmp.weight;
        tmp.parent = NULL;
        tmp.subWeight = 0;
        tmp.nodeNumber = i;
        nodes[i] = tmp;
    }
    
    //建边
    for (int i = 2; i <= n; ++i) {
        int parent; cin >> parent;
        nodes[i].parent = &nodes[parent];
        nodes[parent].children.push_back(&nodes[i]);
    }
    //计算子代和
    sumWeight(&nodes[1]);
    totalWeight = nodes[1].subWeight;
    //查询
    for (int i = 0; i < m; ++i) {
        int number; cin >> number;
        //1为根节点
        root = &nodes[1];
        memset(isDeleted,0,sizeof(int)*MAX_N);
        for (int i = 1; i <= n; ++i) {
            nodes[i].subWeight = nodes[i].subWeightBackup;
        }
        totalWeight = nodes[1].subWeight;
        query(nodes,number);
    }
}