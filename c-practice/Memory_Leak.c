#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* build_message(const char *name) {
    // allocate message "Hello, <name>!"
    size_t n = strlen(name) + 9;
    char *msg = (char*)malloc(n);   // potential leak if not freed by caller
    if (!msg) return NULL;
    snprintf(msg, n, "Hello, %s!", name);
    return msg;
}

int main(void) {
    for (int i = 0; i < 3; ++i) {
        char *m = build_message("world");
        if (!m) return 1;
        printf("%s\n", m);
        // BUG: forgot to free(m); -> leak
    }
    return 0;
}
