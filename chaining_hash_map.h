#ifndef CHAINING_HASH_MAP_H
#define CHAINING_HASH_MAP_H
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
HashMapChaining *newHashMapChaining();
void delHashMapChaining(HashMapChaining *hashMap);
int hashFunc(HashMapChaining *hashMap, int key);
char *get(HashMapChaining *hashMap,int key);
void put(HashMapChaining *hashMap,int key,const char *val);
void removeItem(HashMapChaining *hashMap, int key);
void print(HashMapChaining *hashMap);
#endif