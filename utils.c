#include <stdio.h>
#include <stdlib.h>
int get_int_input(char* input) {
    char *p, s[100];
    long n;
    printf("%s\n", input);

    while (fgets(s, sizeof(s), stdin)) {
        n = strtol(s, &p, 10);
        if (p == s || *p != '\n') {
            printf("Please enter an integer: \n");
        } else break;
    }
    return (int)n;
    // printf("You entered: %ld\n", n);
}