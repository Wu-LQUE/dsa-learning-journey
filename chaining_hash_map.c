#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//键值对 int->string
typedef struct APair
{
    int key;
    char *val;
} Pair;
/* 链表节点 */
typedef struct ANode {
    Pair *pair;
    Node *next;
} Node;
/* 链式地址哈希表 */
typedef struct AHashMapChaining {
    int size;         // 键值对数量
    int capacity;     // 哈希表容量
    double loadThres; // 触发扩容的负载因子阈值
    int extendRatio;  // 扩容倍 数
    Node **buckets;   // 桶数组
} HashMapChaining;

HashMapChaining *newHashMapChaining() {
    HashMapChaining *hashMap = (HashMapChaining*) malloc(sizeof(HashMapChaining));
    hashMap->size = 0;
    hashMap->capacity = 4;
    hashMap->loadThres = 2.0/3.0;
    hashMap->extendRatio = 2;
    hashMap->buckets = (Node **) malloc(hashMap->capacity * sizeof(Node *));
    for(int i = 0; i < hashMap->capacity; i++){
        hashMap->buckets[i] = NULL;
    }
    return hashMap;
}

void delHashMapChaining(HashMapChaining *hashMap){
    for (int i = 0; i < hashMap->capacity; i++) {
        Node *cur = hashMap->buckets[i];
        while(cur){
            Node *tmp = cur;
            cur = cur->next;
            free(tmp->pair);
            free(tmp);
        }
    }
    free(hashMap->buckets);
    free(hashMap);
}

int hashFunc(HashMapChaining *hashMap, int key) {
    return key % hashMap->capacity;
}

/* 负载因子 */
double loadFactor(HashMapChaining *hashMap) {
    return (double)hashMap->size / (double)hashMap->capacity;
}

char *get(HashMapChaining *hashMap,int key) {
    int index = hashFunc(hashMap, key);
    Node *cur = hashMap->buckets[index];
    while (cur) {
        if (cur->pair->key == key) {
            return cur->pair->val;
        }
        cur = cur->next;
    }
}

void put(HashMapChaining *hashMap,int key,const char *val) {
    if (loadFactor(hashMap) > hashMap->loadThres) {
        extend(hashMap);
    }
    int index = hashFunc(hashMap,key);
    Node *cur = hashMap->buckets[index];
    while (cur) {
        if (cur->pair->key == key) {
            if(cur->pair->val) free(cur->pair->val);
            cur->pair->val = (char*) malloc(strlen(val)+1);
            strcpy(cur->pair->val,val);
            return;
        }
        cur = cur->next;
    }
    //如果没有key，则将键值添加到链表头部
    Pair *newPair = (Pair*) malloc(sizeof(Pair));
    newPair->key = key;
    newPair->val = strdup(val);
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->pair = newPair;
    newNode->next = hashMap->buckets[index];
    hashMap->buckets[index] = newNode;
    hashMap->size++;
}

void extend(HashMapChaining *hashMap) {
    int oldCapacity = hashMap->capacity;
    Node **oldBuckets = hashMap->buckets;
    hashMap->capacity = oldCapacity * hashMap->extendRatio;
    hashMap->buckets = (Node **) malloc(hashMap->capacity * sizeof(Node*));
    for (int i = 0; i < hashMap->capacity; i++) {
        hashMap->buckets[i] = NULL;
    }
    hashMap->size = 0;
    for (int i = 0; i < oldCapacity; i++) {
        Node *cur = oldBuckets[i];
        while (cur) {
            put(hashMap,cur->pair->key,cur->pair->val);
            Node *temp = cur;
            cur = cur->next;
            free(temp->pair);
            free(temp);
        }
    }
}

/* 删除操作 */
void removeItem(HashMapChaining *hashMap, int key) {
    int index = hashFunc(hashMap, key);
    Node *cur = hashMap->buckets[index];
    Node *pre = NULL;
    while (cur) {
        if (cur->pair->key == key) {
            // 从中删除键值对
            if (pre) {
                pre->next = cur->next;
            } else {
                hashMap->buckets[index] = cur->next;
            }
            // 释放内存
            free(cur->pair);
            free(cur);
            hashMap->size--;
            return;
        }
        pre = cur;
        cur = cur->next;
    }
}

/* 打印哈希表 */
void print(HashMapChaining *hashMap) {
    for (int i = 0; i < hashMap->capacity; i++) {
        Node *cur = hashMap->buckets[i];
        printf("[");
        while (cur) {
            printf("%d -> %s, ", cur->pair->key, cur->pair->val);
            cur = cur->next;
        }
        printf("]\n");
    }
}