#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} DynamicArray;

DynamicArray* createArray(int capacity) {
    DynamicArray *arr = (DynamicArray*)malloc(sizeof(DynamicArray));
    arr->data = (int*)malloc(sizeof(int) * capacity);
    arr->size = 0;
    arr->capacity = capacity;
    return arr;
}

void insert(DynamicArray *arr, int value) {
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        arr->data = (int*)realloc(arr->data, sizeof(int) * arr->capacity);
    }
    arr->data[arr->size++] = value;
}

void deleteLast(DynamicArray *arr) {
    if (arr->size > 0) {
        arr->size--;
    }
}

void printArray(DynamicArray *arr) {
    for (int i = 0; i < arr->size; i++) {
        printf("%d ", arr->data[i]);
    }
    printf("\n");
}

int main() {
    DynamicArray *arr = createArray(2);
    insert(arr, 10);
    insert(arr, 20);
    insert(arr, 30);
    printArray(arr);
    deleteLast(arr);
    printArray(arr);
    free(arr->data);
    free(arr);
    return 0;
}
// Dynamic array implementation in C