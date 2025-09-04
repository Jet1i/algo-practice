// file: pc_ringbuffer.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int *buf;
    size_t cap, head, tail, size;
    pthread_mutex_t mtx;
    pthread_cond_t not_full, not_empty;
    bool done;
} BQ;

bool bq_init(BQ *q, size_t capacity) {
    q->buf = (int*)malloc(sizeof(int)*capacity);
    if(!q->buf) return false;
    q->cap=capacity; q->head=q->tail=q->size=0; q->done=false;
    pthread_mutex_init(&q->mtx, NULL);
    pthread_cond_init(&q->not_full, NULL);
    pthread_cond_init(&q->not_empty, NULL);
    return true;
}

void bq_destroy(BQ *q) {
    free(q->buf);
    pthread_mutex_destroy(&q->mtx);
    pthread_cond_destroy(&q->not_full);
    pthread_cond_destroy(&q->not_empty);
}

void bq_enqueue(BQ *q, int x) {
    pthread_mutex_lock(&q->mtx);
    while (q->size == q->cap) {
        pthread_cond_wait(&q->not_full, &q->mtx);
    }
    q->buf[q->tail] = x;
    q->tail = (q->tail + 1) % q->cap;
    q->size++;
    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->mtx);
}

bool bq_dequeue(BQ *q, int *out) {
    pthread_mutex_lock(&q->mtx);
    while (q->size == 0 && !q->done) {
        pthread_cond_wait(&q->not_empty, &q->mtx);
    }
    if (q->size == 0 && q->done) {
        pthread_mutex_unlock(&q->mtx);
        return false; // no more items
    }
    *out = q->buf[q->head];
    q->head = (q->head + 1) % q->cap;
    q->size--;
    pthread_cond_signal(&q->not_full);
    pthread_mutex_unlock(&q->mtx);
    return true;
}

typedef struct { BQ *q; int count; } PArg;

void* producer(void *arg) {
    PArg *pa = (PArg*)arg;
    for (int i=1; i<=pa->count; ++i) {
        bq_enqueue(pa->q, i);
        // 模拟生产耗时
        // usleep(1000);
    }
    pthread_mutex_lock(&pa->q->mtx);
    pa->q->done = true;
    pthread_cond_broadcast(&pa->q->not_empty);
    pthread_mutex_unlock(&pa->q->mtx);
    return NULL;
}

void* consumer(void *arg) {
    BQ *q = (BQ*)arg;
    int x;
    long sum = 0;
    while (bq_dequeue(q, &x)) {
        sum += x;
        // 模拟消费耗时
        // usleep(2000);
    }
    printf("[consumer] sum=%ld\n", sum);
    return NULL;
}

int main(void) {
    BQ q;
    if(!bq_init(&q, 8)){ perror("init"); return 1; }

    pthread_t tp, tc;
    PArg pa = { .q=&q, .count=1000 };

    pthread_create(&tp, NULL, producer, &pa);
    pthread_create(&tc, NULL, consumer, &q);

    pthread_join(tp, NULL);
    pthread_join(tc, NULL);

    bq_destroy(&q);
    return 0;
}
