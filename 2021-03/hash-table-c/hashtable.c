#include "hashtable.h"

#include <stdio.h>
#include <stdlib.h>

ListNode *insertNode(ListNode *p, int key, int val) {
    if (p == NULL) return NULL;
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    newNode->key = key;
    newNode->val = val;
    newNode->next = p->next;
    p->next = newNode;
    return newNode;
}

void initialiseHashTable(HashTable *lookup) {
    for (unsigned i = 0; i < 256; ++i) {
        lookup->lookup[i] = (ListNode *)malloc(sizeof(ListNode));
        lookup->lookup[i]->key = 0;
        lookup->lookup[i]->val = 0;
        lookup->lookup[i]->next = NULL;
    }
}

void deleteHashTable(HashTable *lookup) {
    for (unsigned i = 0; i < 256; ++i) {
        ListNode *p = lookup->lookup[i];
        ListNode *nodeToFree;
        while (p) {
            nodeToFree = p;
            p = p->next;
            free(nodeToFree);
        }
    }
    free(lookup);
}

// https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
void shuffle(unsigned char *a, unsigned n) {
    srand(2021);  // any
    for (unsigned i = n - 1; i > 0; --i) {
        unsigned j = rand() % i;
        a[i] ^= a[j] ^= a[i] ^= a[j];
    }
}

void initialiseSeeds(unsigned char *seeds, unsigned n) {
    if (n == 0) return;
    for (int i = 0; i < n; ++i) seeds[i] = i;
    shuffle(seeds, n);
}

// https://en.wikipedia.org/wiki/Pearson_hashing
static inline unsigned char pearson(unsigned x) {
    static int initialised = 0;
    static unsigned char seeds[256];
    if (!initialised) {
        initialiseSeeds(seeds, 256);
        initialised = 1;
    }
    unsigned char hash = 0;
    while (x) {
        hash = seeds[hash ^ (x & 0xff)];
        x >>= 8;
    }
    return hash;
}

int find(HashTable *lookup, int key) {
    unsigned char hash = pearson(key);
    ListNode *p = lookup->lookup[hash]->next;
    while (p && p->key < key) p = p->next;
    if (p && p->key == key) return p->val;
    return -1;
}

int insert(HashTable *lookup, int key, int val) {
    unsigned char hash = pearson(key);
    ListNode *p = lookup->lookup[hash];
    while (p->next && p->next->key < key) p = p->next;
    if (p->next && p->next->key == key) return 0;
    insertNode(p, key, val);
    return 1;
}
