#include <stdio.h>
#include <string.h>
#include <stddef.h>

/* Safe copy:
 * - Copies up to dst_sz-1 bytes from src into dst.
 * - Always NUL-terminates if dst_sz > 0.
 * - Returns the length of src (not the number of bytes copied).
 *   If return >= dst_sz, truncation occurred.
 */
size_t strlcpy_like(char *dst, const char *src, size_t dst_sz) {
    size_t src_len = 0;
    while (src[src_len] != '\0') src_len++;

    if (dst_sz != 0) {
        size_t n = (src_len < (dst_sz - 1)) ? src_len : (dst_sz - 1);
        for (size_t i = 0; i < n; ++i) dst[i] = src[i];
        dst[n] = '\0';
    }
    return src_len;
}

/* Demo & pitfalls discussion */
int main(void) {
    char buf[8];
    size_t need = strlcpy_like(buf, "ABCDEFGH123", sizeof(buf));
    printf("buf=\"%s\" need=%zu dst_sz=%zu %s\n",
           buf, need, sizeof(buf), (need >= sizeof(buf) ? "(truncated)" : ""));
    return 0;
}
