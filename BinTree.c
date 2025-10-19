typedef struct TreeNode * BinTree;
typedef BinTree Position;
struct TreeNode{
    int data;
    BinTree left;
    BinTree right;
};

//三种遍历方式走的路径相同，只是输出值的时机不同
void preOrderTraversal(BinTree bt){
    if(bt){
        printf("%d",bt->data);
        preOrderTraversal(bt->left);
        preOrderTraversal(bt->right);
    }
}
void inOrderTraversal(BinTree bt){
    if(bt){
        inOrderTraversal(bt->left);
        print("%d",bt->data);
        inOrderTraversal(bt->right);
    }
}
void postOrderTraversal(BinTree bt){
    if(bt){
        inOrderTraversal(bt->left);
        inOrderTraversal(bt->right);
        print("%d",bt->data);
    }
}