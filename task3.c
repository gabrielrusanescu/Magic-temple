#include "utils.h"

#define MAX 3500

void sanitizeInput(char *input) {
    for (int i = 0; i < strlen(input); i++) {
        if (strchr("!?.,", input[i]) != NULL) {
            snprintf(input+i, MAX+1, "%s", input+i+1);
            i--;
        }
    }
}

void SolveTask3() {
    int n = 0;
    scanf("%d", &n);
    getchar();
    char text[MAX+1];
    printf("\n");
}