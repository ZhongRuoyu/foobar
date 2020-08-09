#include <stdio.h>

#define MAXLINE 10

void calc_coefficients(double *, int);
void print_coefficients(double *, int);
int abs(int);
double fact(int);

int main(void) {
    for (int line = 0; line <= MAXLINE; line++) {
        double coefficients[2 * line + 1];
        calc_coefficients(coefficients, line);
        print_coefficients(coefficients, line);
    }
    return 0;
}

void calc_coefficients(double *coefficients, int line) {
    for (int index = 0; index < 2 * line + 1; index++) {
        double coefficient = 0;
        int exp = abs(index - line);
        for (int k = 0; exp + 2 * k <= line; k++) {
            coefficient += fact(line) / (fact(line - exp - 2 * k) * fact(exp + k) * fact(k));
        }
        coefficients[index] = coefficient;
    }
}

void print_coefficients(double *coefficients, int line) {
    printf("Line %2d: ", line);
    for (int i = 0; i < 2 * line + 1; i++) {
        printf("%g ", coefficients[i]);
    }
    printf("\b\n");
}

int abs(int n) {
    if (n >= 0) {
        return n;
    } else {
        return -n;
    }
}

double fact(int n) {
    if (n) {
        double factorial = 1;
        while (n >= 1) {
            factorial *= n--;
        }
        return factorial;
    } else {
        return 1;
    }
}