#include <stdio.h>

#define MAXLINE 25

int main(void) {
    double triangle[MAXLINE + 1][2 * MAXLINE + 1]; // A little wasteful, but makes it simpler to calculate
    for (int i = 0; i < MAXLINE; i++) {
        for (int j = 0; j < 2 * MAXLINE + 1; j++) {
            triangle[i][j] = 0;
        }
    }

    for (int line = 0; line <= MAXLINE; line++) {
        for (int index = 0; index < 2 * line + 1; index++) {
            if (index == 0 || index == 2 * line) { // The first/last element in the line
                triangle[line][index] = 1;
            } else if (index == 1) { // The second element in the line
                if (line == 1) { // Line 1: an exception
                    triangle[line][index] = 1;
                } else {
                    triangle[line][index] = triangle[line - 1][index - 1] + triangle[line - 1][index];
                }
            } else if (index == 2 * line) { // The last but second element in the line
                triangle[line][index] = triangle[line - 1][2 * index - 3] + triangle[line - 1][2 * index - 2];
            } else {
                triangle[line][index] = triangle[line - 1][index - 2] + triangle[line - 1][index - 1] + triangle[line - 1][index];
            }
        }
    }

    for (int line = 0; line <= MAXLINE; line++) {
        printf("Line %2d: ", line);
        for (int index = 0; index < 2 * line + 1; index++) {
            printf("%g ", triangle[line][index]);
        }
        printf("\b\n");
    }

    return 0;
}