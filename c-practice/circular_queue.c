#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *buf;
    int capacity;   // total slots
    int head;       // index of current front
    int tail;       // index of next write
    int size;       // current number of elements
} CQueue;

bool cq_init(CQueue *q, int capacity) {
    q->buf = (int*)malloc(sizeof(int) * capacity);
    if (!q->buf) return false;
    q->capacity = capacity;
    q->head = 0;
    q->tail = 0;
    q->size = 0;
    return true;
}

void cq_destroy(CQueue *q) {
    if (q->buf) free(q->buf);
    q->buf = NULL;
    q->capacity = q->head = q->tail = q->size = 0;
}

bool cq_is_empty(const CQueue *q) { return q->size == 0; }
bool cq_is_full (const CQueue *q) { return q->size == q->capacity; }

bool cq_enqueue(CQueue *q, int x) {
    if (cq_is_full(q)) return false;           // full
    q->buf[q->tail] = x;
    q->tail = (q->tail + 1) % q->capacity;
    q->size++;
    return true;
}

bool cq_dequeue(CQueue *q, int *out) {
    if (cq_is_empty(q)) return false;          // empty
    if (out) *out = q->buf[q->head];
    q->head = (q->head + 1) % q->capacity;
    q->size--;
    return true;
}

bool cq_front(const CQueue *q, int *out) {
    if (cq_is_empty(q)) return false;
    if (out) *out = q->buf[q->head];
    return true;
}

/* demo */
int main() {
    CQueue q;
    if (!cq_init(&q, 3)) {                     // capacity=3
        fprintf(stderr, "malloc failed\n");
        return 1;
    }

    printf("enqueue 1,2,3 -> ");
    printf("%d ", cq_enqueue(&q, 1));
    printf("%d ", cq_enqueue(&q, 2));
    printf("%d\n", cq_enqueue(&q, 3));         // should be true until full

    int f;
    cq_front(&q, &f); printf("front=%d\n", f); // 1

    int v;
    cq_dequeue(&q, &v); printf("deq=%d\n", v); // 1
    cq_enqueue(&q, 4);                         // wrap-around write
    cq_front(&q, &f); printf("front=%d\n", f); // 2

    while (cq_dequeue(&q, &v)) printf("pop %d\n", v); // 2,3,4
    printf("empty=%d\n", cq_is_empty(&q));     // 1

    cq_destroy(&q);
    return 0;
}
