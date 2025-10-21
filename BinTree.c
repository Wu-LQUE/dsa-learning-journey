#include "stackTool.h"
#include "queueLink.h"
#include "assert.h"
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
// 创建测试用树的函数
BinTree createTestTree() {
    /* 创建如下结构的二叉树：
          1
        /   \
       2     3
      / \   /
     4   5 6
    */
    
    // 创建节点
    BinTree node1 = (BinTree)malloc(sizeof(struct TreeNode));
    BinTree node2 = (BinTree)malloc(sizeof(struct TreeNode));
    BinTree node3 = (BinTree)malloc(sizeof(struct TreeNode));
    BinTree node4 = (BinTree)malloc(sizeof(struct TreeNode));
    BinTree node5 = (BinTree)malloc(sizeof(struct TreeNode));
    BinTree node6 = (BinTree)malloc(sizeof(struct TreeNode));
    
    // 设置节点数据
    node1->data = 1;
    node2->data = 2;
    node3->data = 3;
    node4->data = 4;
    node5->data = 5;
    node6->data = 6;
    
    // 构建树结构
    node1->left = node2;
    node1->right = node3;
    
    node2->left = node4;
    node2->right = node5;
    
    node3->left = node6;
    node3->right = NULL;
    
    node4->left = NULL;
    node4->right = NULL;
    
    node5->left = NULL;
    node5->right = NULL;
    
    node6->left = NULL;
    node6->right = NULL;
    
    return node1;
}

// 创建测试用树的函数
BinTree createTestBstTree() {
    /* 创建如下结构的二叉树：
          4
        /   \
       2     5
      / \     \
     1   3     6
    */
    
    // 创建节点
    BinTree node1 = (BinTree)malloc(sizeof(struct TreeNode));
    BinTree node2 = (BinTree)malloc(sizeof(struct TreeNode));
    BinTree node3 = (BinTree)malloc(sizeof(struct TreeNode));
    BinTree node4 = (BinTree)malloc(sizeof(struct TreeNode));
    BinTree node5 = (BinTree)malloc(sizeof(struct TreeNode));
    BinTree node6 = (BinTree)malloc(sizeof(struct TreeNode));
    
    // 设置节点数据
    node1->data = 4;
    node2->data = 2;
    node3->data = 5;
    node4->data = 1;
    node5->data = 3;
    node6->data = 6;
    
    // 构建树结构
    node1->left = node2;
    node1->right = node3;
    
    node2->left = node4;
    node2->right = node5;
    
    node3->left = NULL;
    node3->right = node6;
    
    node4->left = NULL;
    node4->right = NULL;
    
    node5->left = NULL;
    node5->right = NULL;
    
    node6->left = NULL;
    node6->right = NULL;
    
    return node1;
}
void freeBinTree(BinTree bt){
    if(bt){
        freeBinTree(bt->left);
        freeBinTree(bt->right);
        free(bt);
    }
}
//三种遍历方式走的路径相同，只是输出值的时机不同
void preOrderTraversal(BinTree bt){
    if(bt){
        printf("%d ",bt->data);
        preOrderTraversal(bt->left);
        preOrderTraversal(bt->right);
    }
}
void inOrderTraversal(BinTree bt){
    if(bt){
        inOrderTraversal(bt->left);
        printf("%d ",bt->data);
        inOrderTraversal(bt->right);
    }
}
void postOrderTraversal(BinTree bt){
    if(bt){
        inOrderTraversal(bt->left);
        inOrderTraversal(bt->right);
        printf("%d ",bt->data);
    }
}
//使用栈实现的中序遍历
void inOrderTraversal_stack(BinTree bt){
    Stack stack = createStack();
    BinTree t = bt;
    while(t||!isEmpty(stack)){
        while(t){
            push(stack,t);
            t=t->left;
        }
        if(!isEmpty(stack)){
            t = pop(stack);
            printf("%d ",t->data);
            t = t->right;
        }
    }
    free(stack);
}
//层序遍历
void layerTraversal(BinTree bt){
    Queue queue = createQueue();
    destroyQueue(queue);
}

BinTree findElement(TreeNodeDataType x,BinTree bst){
    if(!bst) return NULL;
    if(x==bst->data)
        return bst;
    else if(x>bst->data)
        return findElement(x,bst->right);
    else
        return findElement(x,bst->left);
}
BinTree iterFindElement(TreeNodeDataType x,BinTree bst){
    while (bst)
    {
        if(x == bst->data){
            return bst;
        }else if (x < bst->data)
        {
            bst = bst->left;
        }else{
            bst = bst->right;
        }        
    }
    return NULL;
}
BinTree findMin(BinTree bst){
    if(!bst) return NULL;
    // int min = bst->data;
    while(bst->left){
        bst = bst->left;
    }
    // min = bst->data;
    return bst;
}
BinTree findMax(BinTree bst){
    if(!bst) return NULL;
    if(bst->right) return findMax(bst->right);
    else return bst; 
}
void insertToBst(TreeNodeDataType x ,BinTree bst){
    if(!bst){
        BinTree insertNode = createBinTreeWithData(x);
        bst = insertNode;
    }else if (x > bst->data){
        if(bst->right==NULL){
            BinTree insertNode = createBinTreeWithData(x);
            bst->right = insertNode;
        }else{
            insertToBst(x,bst->right);
        }
    }else if (x == bst->data){
        return;
    }else{//x < bst->data
        if(bst->left==NULL){
            BinTree insertNode = createBinTreeWithData(x);
            bst->left = insertNode;
        }else{
            insertToBst(x,bst->left);
        }
    }
}
BinTree refineInsertToBst(TreeNodeDataType x ,BinTree bst){
    if(!bst){
        BinTree insertNode = createBinTreeWithData(x);
        return insertNode;
    }else if (x > bst->data){
        bst->right = refineInsertToBst(x,bst->right);
    }else if (x == bst->data){
        return bst;
    }else{//x < bst->data
        bst->left = refineInsertToBst(x,bst->left);
    }
    return bst;
}
int test(){
    BinTree bt = createTestBstTree();
     /* 创建如下结构的二叉树：
          4
        /   \
       2     5
      / \     \
     1   3     6
    */
    // printf("递归中序遍历测试树\n");
    // inOrderTraversal(bt);
    // printf("\n借助栈实现中序遍历测试树\n");
    // inOrderTraversal_stack(bt);
    // printf("前序遍历二叉搜索树\n");
    // preOrderTraversal(bt);
    assert(bt->data==4&&bt->left->data==2&&bt->right->data==5&&bt->left->left->data==1&&bt->left->right->data==3&&bt->right->right->data==6);
    // printf("\n");
    int target = 5;
    BinTree pos = findElement(target,bt);
    // printf("find %d in %d\n",target,pos->data);
    assert(pos->data==target&&pos->right->data==6);
    pos = iterFindElement(target,bt);
    // printf("find %d in %d\n",target,pos->data);
    assert(pos->data==target&&pos->right->data==6);
    pos = findMin(bt);
    assert(pos&&pos->data==1);
    pos = findMax(bt);
    assert(pos&&pos->data==6);
    printf("passCreateAndSearchTests\n");
    insertToBst(5,bt);
    assert(bt->data==4&&bt->left->data==2&&bt->right->data==5&&bt->left->left->data==1&&bt->left->right->data==3&&bt->right->right->data==6);
    insertToBst(4,bt);
    assert(bt->data==4&&bt->left->data==2&&bt->right->data==5&&bt->left->left->data==1&&bt->left->right->data==3&&bt->right->right->data==6);
    //有所变化的插入
    insertToBst(8,bt);
    assert(bt->right->right->right->data==8&&bt->data==4&&bt->left->data==2&&bt->right->data==5&&bt->left->left->data==1&&bt->left->right->data==3&&bt->right->right->data==6);
    insertToBst(7,bt);
    assert(bt->right->right->right->left->data==7&&bt->right->right->right->data==8&&bt->data==4&&bt->left->data==2&&bt->right->data==5&&bt->left->left->data==1&&bt->left->right->data==3&&bt->right->right->data==6);
    freeBinTree(bt);
    printf("passCreate,Search,Insert,Tests\n");
    return 1;
}
int testRefineInsert(){
    BinTree bt = createTestBstTree();
    refineInsertToBst(5,bt);
    assert(bt->data==4&&bt->left->data==2&&bt->right->data==5&&bt->left->left->data==1&&bt->left->right->data==3&&bt->right->right->data==6);
    refineInsertToBst(4,bt);
    assert(bt->data==4&&bt->left->data==2&&bt->right->data==5&&bt->left->left->data==1&&bt->left->right->data==3&&bt->right->right->data==6);
    //有所变化的插入
    refineInsertToBst(8,bt);
    assert(bt->right->right->right->data==8&&bt->data==4&&bt->left->data==2&&bt->right->data==5&&bt->left->left->data==1&&bt->left->right->data==3&&bt->right->right->data==6);
    refineInsertToBst(7,bt);
    assert(bt->right->right->right->left->data==7&&bt->right->right->right->data==8&&bt->data==4&&bt->left->data==2&&bt->right->data==5&&bt->left->left->data==1&&bt->left->right->data==3&&bt->right->right->data==6);
    freeBinTree(bt);
    printf("pass refineInsert Tests\n");
    return 1;
}
int main(){
    test();
    testRefineInsert();
}