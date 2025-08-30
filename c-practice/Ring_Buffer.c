#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint8_t *data;
    size_t cap;   // capacity, power-of-two preferred
    size_t head;  // read index
    size_t tail;  // write index
} RingBuf;

static size_t next_pow2(size_t x){
    size_t p = 1; while (p < x) p <<= 1; return p;
}

bool rb_init(RingBuf *rb, size_t capacity){
    if (capacity < 2) capacity = 2;
    rb->cap = next_pow2(capacity);
    rb->data = (uint8_t*)malloc(rb->cap);
    if (!rb->data) return false;
    rb->head = rb->tail = 0;
    return true;
}

void rb_free(RingBuf *rb){
    if (!rb) return;
    free(rb->data); rb->data = NULL;
    rb->cap = rb->head = rb->tail = 0;
}

static inline size_t rb_mask(const RingBuf *rb){ return rb->cap - 1; }
static inline size_t rb_size(const RingBuf *rb){ return rb->tail - rb->head; }
static inline size_t rb_capacity(const RingBuf *rb){ return rb->cap; }
static inline size_t rb_space(const RingBuf *rb){ return rb->cap - rb_size(rb); }
static inline bool   rb_is_empty(const RingBuf *rb){ return rb_size(rb) == 0; }
static inline bool   rb_is_full (const RingBuf *rb){ return rb_size(rb) == rb->cap; }

/* Write up to n bytes, return actually written bytes */
size_t rb_write(RingBuf *rb, const uint8_t *src, size_t n){
    size_t can = rb_space(rb);
    if (n > can) n = can;
    size_t mask = rb_mask(rb);
    size_t t = rb->tail & mask;

    size_t first = rb->cap - t;           // first chunk to end
    if (first > n) first = n;
    memcpy(&rb->data[t], src, first);
    memcpy(&rb->data[0], src + first, n - first);
    rb->tail += n;
    return n;
}

/* Read up to n bytes, return actually read bytes */
size_t rb_read(RingBuf *rb, uint8_t *dst, size_t n){
    size_t can = rb_size(rb);
    if (n > can) n = can;
    size_t mask = rb_mask(rb);
    size_t h = rb->head & mask;

    size_t first = rb->cap - h;
    if (first > n) first = n;
    memcpy(dst, &rb->data[h], first);
    memcpy(dst + first, &rb->data[0], n - first);
    rb->head += n;
    return n;
}

/* -------- small tests -------- */
static void hexdump(const uint8_t *p, size_t n){
    for(size_t i=0;i<n;i++) printf("%02X%s", p[i], (i+1<n)?" ":"");
    printf("\n");
}

int main(void){
    RingBuf rb;
    if(!rb_init(&rb, 8)){ fprintf(stderr, "init failed\n"); return 1; }

    uint8_t out[64];

    // 1) simple write+read
    const uint8_t a[] = {1,2,3,4,5};
    size_t w = rb_write(&rb, a, sizeof(a));
    printf("wrote=%zu size=%zu space=%zu\n", w, rb_size(&rb), rb_space(&rb));
    size_t r = rb_read(&rb, out, 3);
    printf("read=%zu size=%zu space=%zu -> ", r, rb_size(&rb), rb_space(&rb)); hexdump(out, r);

    // 2) wrap-around write
    const uint8_t b[] = {6,7,8,9,10,11,12,13};
    w = rb_write(&rb, b, sizeof(b));  // should wrap
    printf("wrote2=%zu size=%zu space=%zu\n", w, rb_size(&rb), rb_space(&rb));

    // 3) read all
    r = rb_read(&rb, out, sizeof(out));
    printf("read2=%zu size=%zu space=%zu -> ", r, rb_size(&rb), rb_space(&rb)); hexdump(out, r);

    // 4) partial write/partial read edge
    const uint8_t c[] = {0xAA,0xBB,0xCC};
    rb_write(&rb, c, 3);
    r = rb_read(&rb, out, 1);
    printf("read3=%zu -> ", r); hexdump(out, r);
    r = rb_read(&rb, out, 5); // more than available
    printf("read4=%zu -> ", r); hexdump(out, r);

    rb_free(&rb);
    return 0;
}
