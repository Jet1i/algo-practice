#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int val;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    size_t sz;
} LStack;

void ls_init(LStack* s) { s->head = NULL; s->sz = 0; }

bool ls_is_empty(const LStack* s) { return s->sz == 0; }
size_t ls_size(const LStack* s) { return s->sz; }

bool ls_push(LStack* s, int x) {
    Node* n = (Node*)malloc(sizeof(Node));
    if (!n) return false;
    n->val = x;
    n->next = s->head;
    s->head = n;
    s->sz++;
    return true;
}

bool ls_top(const LStack* s, int* out) {
    if (ls_is_empty(s)) return false;
    if (out) *out = s->head->val;
    return true;
}

bool ls_pop(LStack* s, int* out) {
    if (ls_is_empty(s)) return false;
    Node* n = s->head;
    if (out) *out = n->val;
    s->head = n->next;
    free(n);
    s->sz--;
    return true;
}

void ls_destroy(LStack* s) {
    Node* cur = s->head;
    while (cur) {
        Node* nxt = cur->next;
        free(cur);
        cur = nxt;
    }
    s->head = NULL;
    s->sz = 0;
}

/* mini test */
int main(void) {
    LStack s; ls_init(&s);
    for (int i = 1; i <= 3; ++i) ls_push(&s, i*10);   // 10,20,30 (top=30)
    int x;
    ls_top(&s, &x); printf("top=%d size=%zu\n", x, ls_size(&s));   // 30,3
    while (ls_pop(&s, &x)) printf("pop %d\n", x);                  // 30,20,10
    printf("empty=%d size=%zu\n", (int)ls_is_empty(&s), ls_size(&s)); // 1,0
    ls_destroy(&s);
    return 0;
}
