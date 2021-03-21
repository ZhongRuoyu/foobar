#ifndef HASHTABLE_H_

#define HASHTABLE_H_

typedef struct ListNode {
    int key;
    int val;
    struct ListNode *next;
} ListNode;

typedef struct HashTable {
    ListNode *lookup[256];
} HashTable;

ListNode *insertNode(ListNode *p, int key, int val);

void shuffle(unsigned char *a, unsigned n);
void initialiseSeeds(unsigned char *seeds, unsigned n);
static inline unsigned char pearson(unsigned x);

void initialiseHashTable(HashTable *lookup);
void deleteHashTable(HashTable *lookup);
int find(HashTable *lookup, int key);
int insert(HashTable *lookup, int key, int val);

#endif  // HASHTABLE_H_
