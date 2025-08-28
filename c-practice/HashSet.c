#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum { EMPTY=0, FILLED=1, DELETED=2 } SlotState;

typedef struct {
    int *keys;
    SlotState *state;
    int capacity;  // use a prime or power-of-two; here choose power-of-two for fast mod
    int size;
} HashSet;

static inline uint32_t hash32(uint32_t x) {
    // a simple integer mix (xorshift-like)
    x ^= x >> 16; x *= 0x7feb352d;
    x ^= x >> 15; x *= 0x846ca68b;
    x ^= x >> 16;
    return x;
}

bool hs_init(HashSet *hs, int capacity) {
    if (capacity < 8) capacity = 8;
    // round to power of two for fast modulo
    int cap = 1; while (cap < capacity) cap <<= 1;
    hs->capacity = cap;
    hs->size = 0;
    hs->keys  = (int*)malloc(sizeof(int) * hs->capacity);
    hs->state = (SlotState*)malloc(sizeof(SlotState) * hs->capacity);
    if (!hs->keys || !hs->state) return false;
    for (int i = 0; i < hs->capacity; ++i) hs->state[i] = EMPTY;
    return true;
}

void hs_free(HashSet *hs) {
    if (!hs) return;
    free(hs->keys);
    free(hs->state);
    hs->keys = NULL;
    hs->state = NULL;
    hs->capacity = hs->size = 0;
}

static int hs_find_slot(HashSet *hs, int key, bool for_insert) {
    uint32_t h = hash32((uint32_t)key);
    int mask = hs->capacity - 1;
    int first_deleted = -1;
    for (int i = 0; i < hs->capacity; ++i) {
        int idx = (h + i) & mask;           // linear probing
        if (hs->state[idx] == FILLED) {
            if (hs->keys[idx] == key) return idx; // found
        } else if (hs->state[idx] == DELETED) {
            if (for_insert && first_deleted < 0) first_deleted = idx;
        } else { // EMPTY
            return for_insert && first_deleted >= 0 ? first_deleted : idx;
        }
    }
    return -1; // table full (shouldn’t happen if load factor is controlled)
}

bool hs_contains(HashSet *hs, int key) {
    int idx = hs_find_slot(hs, key, false);
    return (idx >= 0 && hs->state[idx] == FILLED && hs->keys[idx] == key);
}

bool hs_insert(HashSet *hs, int key) {
    int idx = hs_find_slot(hs, key, true);
    if (idx < 0) return false;
    if (hs->state[idx] == FILLED && hs->keys[idx] == key) return true; // already in set
    hs->keys[idx] = key;
    hs->state[idx] = FILLED;
    hs->size++;
    return true;
}

bool hs_remove(HashSet *hs, int key) {
    int idx = hs_find_slot(hs, key, false);
    if (idx < 0 || hs->state[idx] != FILLED || hs->keys[idx] != key) return false;
    hs->state[idx] = DELETED;  // leave tombstone
    hs->size--;
    return true;
}

/* demo */
int main(void) {
    HashSet hs;
    if (!hs_init(&hs, 16)) {
        fprintf(stderr, "init failed\n");
        return 1;
    }
    hs_insert(&hs, 10);
    hs_insert(&hs, 42);
    hs_insert(&hs, -7);
    printf("contains 42? %d\n", hs_contains(&hs, 42));  // 1
    printf("contains 11? %d\n", hs_contains(&hs, 11));  // 0
    hs_remove(&hs, 42);
    printf("contains 42? %d\n", hs_contains(&hs, 42));  // 0
    hs_free(&hs);
    return 0;
}
