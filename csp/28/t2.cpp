#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct tree{
    ll p;
    ll t;
    ll depth;
    ll early;
    vector<tree*> children;
    tree() : p(0),t(0),depth(0) {};
};

ll dfs(tree* root,vector<tree*> &arr) {
    ll maxDepth = 0;
    if (root->p == 0) root->early = 1;
    else root->early = arr[root->p]->early+arr[root->p]->t;
    for (ll i = 0; i < root->children.size(); ++i) {
        maxDepth = max(maxDepth,dfs(root->children[i],arr));
    }
    root->depth = maxDepth+root->t;
    return maxDepth+root->t;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    freopen("t2.txt","r",stdin);
    ll n,m; cin >> n >> m;
    vector<tree*> arr(m+1); for (ll i = 1; i <= m; ++i) arr[i] = new tree();
    for (ll i = 1; i <= m; ++i) {
        tree *cur = arr[i]; cin >> cur->p;
        if (cur->p == 0) continue;
        arr[cur->p]->children.push_back(cur);
    }
    for (ll i = 1; i <= m; ++i) {
        tree *cur = arr[i]; cin >> cur->t;
    }
    ll maxRootDepth = 0;
    //计算depth
    for (ll i = 1; i <= m; ++i) {
        tree *cur = arr[i];
        if (cur->p==0) {
            //root
            cur->depth == dfs(cur,arr);
            maxRootDepth = max(maxRootDepth,cur->depth);
        }
    }
    for (ll i = 1; i <= m; ++i) {
        tree *cur = arr[i];
        cout << cur->early << " ";
    }
    cout << endl;
    if (maxRootDepth > n) return 0;
    for (ll i = 1; i <= m; ++i) {
        tree *cur = arr[i];
        ll late = n - cur->depth + 1;
        cout << late << " ";
    }
    cout << endl;
}