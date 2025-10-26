#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 20
//键值对 int->string
typedef struct APair
{
    int key;
    char *val;
} Pair;
typedef struct APairMapSet {
    Pair *set;
    int len;
} PairMapSet;
typedef struct AKeyMapSet {
    int *set;
    int len;
} KeyMapSet;
typedef struct AValMapSet {
    char **set;
    int len;
} ValMapSet;

typedef struct 
{
    Pair *buckets[MAXSIZE];
} ArrayHashMap;

ArrayHashMap *newArrayHashMap(){
    ArrayHashMap *hmap =(ArrayHashMap*) malloc(sizeof(ArrayHashMap));
    for (int i=0;i<MAXSIZE;i++) {
        hmap->buckets[i] = NULL;
    }
    return hmap;
}
//析构函数
void delArrayHashMap(ArrayHashMap *hmap){
    for (int i = 0;i<MAXSIZE;i++) {
        if (hmap->buckets[i]!=NULL) {
            free(hmap->buckets[i]->val);
            free(hmap->buckets[i]);
        }
    }
    free(hmap);
}

//碰碰车式哈希函数,后面再改
int hashFunc(const int key) {
    return key % MAXSIZE;
}

void put(ArrayHashMap *hmap,const int key,const char *val){
    Pair *pair =(Pair*) malloc(sizeof(Pair));
    pair->key = key;
    pair->val =(char*) malloc(strlen(val)+1);
    strncpy(pair->val,val,strlen(val)+1);
    int index = hashFunc(key);
    hmap->buckets[index] = pair;
}

void removeItem(ArrayHashMap *hmap,const int key){
    int index = hashFunc(key);
    free(hmap->buckets[index]->val);
    free(hmap->buckets[index]);
    hmap->buckets[index]=NULL;
}

void pairSet(ArrayHashMap *hmap,PairMapSet *set){
    Pair *entries;
    int i = 0,index = 0;
    int total = 0;
    for (i = 0; i < MAXSIZE; i++) {
        if(hmap->buckets[i] != NULL){
            total++;
        }
    }
    entries =(Pair*) malloc(sizeof(Pair) * total);
    for (i = 0; i < MAXSIZE; i++) {
        if (hmap->buckets[i] != NULL) {
            entries[index].key = hmap->buckets[i]->key;
            entries[index].val = strdup(hmap->buckets[i]->val);
            index++;
        }
    }
    set->set = entries;
    set->len = total;
}

void keySet(ArrayHashMap *hmap,KeyMapSet *set){
    int *keys;
    int i = 0;
    int total = 0;
    for (i = 0; i < MAXSIZE; i++){
        if(hmap->buckets[i]!=NULL){
            total++;
        }
    }
    keys =(int*) malloc(total * sizeof(int));
    int index = 0;
    for (i = 0; i < MAXSIZE; i++){
        if(hmap->buckets[i]!=NULL){
            keys[index] = hmap->buckets[i]->key;
            index++;
        }
    }
    set->set = keys;
    set->len = total;
}

void valueSet(ArrayHashMap *hmap,ValMapSet *set){
    char **vals;
    int i = 0,index = 0;
    int total = 0;
    for (i = 0; i < MAXSIZE; i++) {
        if(hmap->buckets[i] != NULL){
            total++;
        }
    }
    vals =(char **) malloc(total * sizeof(char*));
    for (i = 0; i < MAXSIZE; i++) {
        if (hmap->buckets[i]!=NULL) {
            vals[index] = hmap->buckets[i]->val;
            index++;
        }
    }
    set->set = vals;
    set->len = total;
}

void printArrayHashMap(ArrayHashMap *hmap){
    PairMapSet set;
    pairSet(hmap,&set);
    Pair *entries = set.set;
    for(int i = 0; i < set.len; i++){
        printf("%d:%s\n",entries[i].key,entries[i].val);
    }
    free(set.set);
}

int main(){
    ArrayHashMap *hmap = newArrayHashMap();
    put(hmap,1,"test1");
    put(hmap,0,"test2");
    printArrayHashMap(hmap);
}