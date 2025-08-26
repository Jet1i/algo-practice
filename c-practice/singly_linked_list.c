#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int val;
    struct Node* next;
} Node;

Node* new_node(int v) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->val = v;
    n->next = NULL;
    return n;
}

void push_front(Node** head, int v) {
    Node* n = new_node(v);
    n->next = *head;
    *head = n;
}

void push_back(Node** head, int v) {
    Node* n = new_node(v);
    if (*head == NULL) { *head = n; return; }
    Node* cur = *head;
    while (cur->next) cur = cur->next;
    cur->next = n;
}

bool delete_value(Node** head, int v) {
    if (*head == NULL) return false;
    if ((*head)->val == v) {
        Node* tmp = *head;
        *head = (*head)->next;
        free(tmp);
        return true;
    }
    Node* cur = *head;
    while (cur->next && cur->next->val != v) cur = cur->next;
    if (cur->next == NULL) return false;
    Node* tmp = cur->next;
    cur->next = tmp->next;
    free(tmp);
    return true;
}

void print_list(Node* head) {
    for (Node* p = head; p; p = p->next) {
        printf("%d%s", p->val, p->next ? " -> " : "\n");
    }
}

void free_list(Node** head) {
    Node* cur = *head;
    while (cur) {
        Node* nxt = cur->next;
        free(cur);
        cur = nxt;
    }
    *head = NULL;
}

int main() {
    Node* head = NULL;
    // test
    push_back(&head, 10);
    push_back(&head, 20);
    push_front(&head, 5);
    print_list(head);           // 5 -> 10 -> 20
    delete_value(&head, 10);
    print_list(head);           // 5 -> 20
    free_list(&head);
    return 0;
}
