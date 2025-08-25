#include <stdio.h>
#include <string.h>

void reverse(char *str) {
    int left = 0;
    int right = strlen(str) - 1;
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

int main() {
    char str1[] = "hello";
    char str2[] = "world";

    printf("Original str1: %s\n", str1);
    reverse(str1);
    printf("Reversed with custom reverse: %s\n", str1);

    printf("Original str2: %s\n", str2);
    printf("Reversed with strrev: %s\n", strrev(str2));

    return 0;
}
