#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    unsigned char *bits;
    size_t nbits;      // total bits
    size_t nbytes;     // allocated bytes
} Bitset;

static inline size_t _byte_idx(size_t x) { return x >> 3; }   // x / 8
static inline unsigned _bit_mask(size_t x) { return 1u << (x & 7); } // x % 8

bool bs_init(Bitset *bs, size_t nbits) {
    bs->nbits = nbits;
    bs->nbytes = (nbits + 7) / 8;
    bs->bits = (unsigned char*)calloc(bs->nbytes, 1);
    return bs->bits != NULL;
}

void bs_free(Bitset *bs) {
    if (bs->bits) free(bs->bits);
    bs->bits = NULL; bs->nbits = bs->nbytes = 0;
}

bool bs_set(Bitset *bs, size_t x) {
    if (x >= bs->nbits) return false;
    bs->bits[_byte_idx(x)] |= _bit_mask(x);
    return true;
}

bool bs_clear(Bitset *bs, size_t x) {
    if (x >= bs->nbits) return false;
    bs->bits[_byte_idx(x)] &= (unsigned char)(~_bit_mask(x));
    return true;
}

bool bs_test(const Bitset *bs, size_t x) {
    if (x >= bs->nbits) return false;
    return (bs->bits[_byte_idx(x)] & _bit_mask(x)) != 0;
}

/* demo: build set {1, 3, 8}, test membership */
int main(void) {
    Bitset bs;
    if (!bs_init(&bs, 100)) { fprintf(stderr, "init failed\n"); return 1; }
    bs_set(&bs, 1); bs_set(&bs, 3); bs_set(&bs, 8);
    printf("has 3? %d\n", bs_test(&bs, 3));  // 1
    printf("has 2? %d\n", bs_test(&bs, 2));  // 0
    bs_clear(&bs, 3);
    printf("has 3? %d\n", bs_test(&bs, 3));  // 0
    bs_free(&bs);
    return 0;
}
