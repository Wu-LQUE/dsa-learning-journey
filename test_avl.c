#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "BinTree.h"  // 需提供 BinTree、TreeNodeDataType、struct TreeNode、createBinTreeWithData 等声明
#include "avl.h"      // 需提供 avl_insert 声明
BinTree createBinTree(){
    BinTree root = (BinTree) malloc(sizeof(struct TreeNode));
    root->data = 0;
    root->left = NULL;
    root->right = NULL;
    return root;
}
BinTree createBinTreeWithData(TreeNodeDataType data){
    BinTree root = (BinTree) malloc(sizeof(struct TreeNode));
    root->data = data;
    root->left = NULL;
    root->right = NULL;
    return root;
}
int calculateFactor(BinTree bt){
    if(!bt) return 0;
    int H_Left = getHeight(bt->left);
    int H_Right = getHeight(bt->right);
    return H_Left - H_Right;
}
int getHeight(BinTree bt){
    if(!bt) return 0;//空树深度为0
    if(!bt->left&&!bt->right) return 1;//叶子节点
    int leftHeight = getHeight(bt->left);
    int rightHeight = getHeight(bt->right);
    int max = leftHeight >= rightHeight ? leftHeight : rightHeight;
    return max+1;
}
// ---------- 辅助检查函数（仅用于测试） ----------
static int nodeHeight(BinTree n) {
    if (!n) return 0;
    int lh = nodeHeight(n->left);
    int rh = nodeHeight(n->right);
    return (lh > rh ? lh : rh) + 1;
}

static bool isBalanced(BinTree n) {
    if (!n) return true;
    int bf = nodeHeight(n->left) - nodeHeight(n->right);
    if (bf < -1 || bf > 1) return false;
    return isBalanced(n->left) && isBalanced(n->right);
}

static void inorderCollect(BinTree n, TreeNodeDataType* arr, int* idx) {
    if (!n) return;
    inorderCollect(n->left, arr, idx);
    arr[(*idx)++] = n->data;
    inorderCollect(n->right, arr, idx);
}

static bool isStrictlySorted(const TreeNodeDataType* a, int n) {
    for (int i = 1; i < n; ++i) {
        if (!(a[i-1] < a[i])) return false;
    }
    return true;
}

static void freeTree(BinTree n) {
    if (!n) return;
    freeTree(n->left);
    freeTree(n->right);
    free(n);
}

static void assertAVLAndBST(BinTree root, int expectedCount) {
    // 检查平衡
    assert(isBalanced(root) && "Tree is not AVL-balanced");
    // 中序应严格递增（BST）
    TreeNodeDataType* arr = (TreeNodeDataType*)malloc(sizeof(TreeNodeDataType) * (expectedCount > 0 ? expectedCount : 1));
    int idx = 0;
    inorderCollect(root, arr, &idx);
    assert(idx == expectedCount && "Node count mismatch");
    assert(isStrictlySorted(arr, idx) && "Inorder is not strictly increasing (BST violated or duplicates inserted)");
    free(arr);
}

// ---------- 测试用例 ----------

// LL 型：插入 3,2,1
static void test_LL() {
    BinTree t = NULL;
    t = avl_insert(t, 3);
    t = avl_insert(t, 2);
    t = avl_insert(t, 1);
    // 期望旋转后：根为 2，左 1，右 3
    assert(t && t->data == 2);
    assert(t->left && t->left->data == 1);
    assert(t->right && t->right->data == 3);
    assertAVLAndBST(t, 3);
    freeTree(t);
    printf("test_LL passed\n");
}

// RR 型：插入 1,2,3
static void test_RR() {
    BinTree t = NULL;
    t = avl_insert(t, 1);
    t = avl_insert(t, 2);
    t = avl_insert(t, 3);
    // 期望旋转后：根为 2，左 1，右 3
    assert(t && t->data == 2);
    assert(t->left && t->left->data == 1);
    assert(t->right && t->right->data == 3);
    assertAVLAndBST(t, 3);
    freeTree(t);
    printf("test_RR passed\n");
}

// LR 型：插入 3,1,2
static void test_LR() {
    BinTree t = NULL;
    t = avl_insert(t, 3);
    t = avl_insert(t, 1);
    t = avl_insert(t, 2);
    // 期望双旋后：根为 2，左 1，右 3
    assert(t && t->data == 2);
    assert(t->left && t->left->data == 1);
    assert(t->right && t->right->data == 3);
    assertAVLAndBST(t, 3);
    freeTree(t);
    printf("test_LR passed\n");
}

// RL 型：插入 1,3,2
static void test_RL() {
    BinTree t = NULL;
    t = avl_insert(t, 1);
    t = avl_insert(t, 3);
    t = avl_insert(t, 2);
    // 期望双旋后：根为 2，左 1，右 3
    assert(t && t->data == 2);
    assert(t->left && t->left->data == 1);
    assert(t->right && t->right->data == 3);
    assertAVLAndBST(t, 3);
    freeTree(t);
    printf("test_RL passed\n");
}

// 经典序列：10,20,30,40,50,25（会触发 RL），最终根应为 30
static void test_long_sequence() {
    BinTree t = NULL;
    int seq[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(seq)/sizeof(seq[0]);
    for (int i = 0; i < n; ++i) {
        t = avl_insert(t, seq[i]);
    }
    // 经典结果：根 30；左子 20（含 10,25），右子 40（含 50）
    assert(t && t->data == 30);
    assert(t->left && t->left->data == 20);
    assert(t->left->left && t->left->left->data == 10);
    assert(t->left->right && t->left->right->data == 25);
    assert(t->right && t->right->data == 40);
    assert(t->right->right && t->right->right->data == 50);
    assertAVLAndBST(t, n);
    freeTree(t);
    printf("test_long_sequence passed\n");
}

// 重复键：重复插入不应改变结构或节点数
static void test_duplicates() {
    BinTree t = NULL;
    t = avl_insert(t, 5);
    t = avl_insert(t, 5); // 重复
    t = avl_insert(t, 3);
    t = avl_insert(t, 7);
    // 只应有三个节点：3,5,7
    assertAVLAndBST(t, 3);
    // 根可能是 5（常见），这里不强制根值，只检查 BST/AVL 和节点数
    freeTree(t);
    printf("test_duplicates passed\n");
}

int main(void) {
    test_LL();
    test_RR();
    test_LR();
    test_RL();
    test_long_sequence();
    test_duplicates();
    printf("All AVL insert tests passed.\n");
    return 0;
}