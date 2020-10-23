#include <stdio.h>

void inputMatrix(int n, double matrix[][n]);
void printMatrix(int n, double matrix[][n]);
void minor(int n, double matrix[][n], double minor[][n - 1], int mi, int mj);
double cofactor(int n, double matrix[][n], int ci, int cj);
double determinant(int n, double matrix[][n]);
void invert(int n, double matrix[][n], double inverse[][n], double det);

int main(void) {
    int n;
    printf("This program can:\n");
    printf("- calculate the determinant of an n*n matrix using Laplace expansion;\n");
    printf("- and calculate its inverse, if exists.\n");
    while (1) {
        printf("Please enter n: ");
        scanf("%d", &n);
        if (n > 0) break;
        printf("n should be a positive integer. Please try again.\n");
    }
    double matrix[n][n];
    double det;
    inputMatrix(n, matrix);
    det = determinant(n, matrix);
    printf("The determinant of the matrix is %g.\n", det);
    if (det) {
        double inverse[n][n];
        invert(n, matrix, inverse, det);
        printf("Its inverse is:\n");
        printMatrix(n, inverse);
    } else {
        printf("It is not invertible.\n");
    }
    return 0;
}

void inputMatrix(int n, double matrix[][n]) {
    if (n > 1) printf("Please seperate the numbers using spaces.\n");
    for (int i = 0; i < n; i++) {
        printf("Please input row %d: ", i + 1);
        for (int j = 0; j < n; j++) {
            scanf("%lf", &matrix[i][j]);
        }
    }
}

void printMatrix(int n, double matrix[][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%4g ", matrix[i][j]);
        }
        printf("\n");
    }
}

void minor(int n, double matrix[][n], double m[][n - 1], int mi, int mj) {
    double *pmatrix = &matrix[0][0], *pm = &m[0][0];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != mi && j != mj) {
                *(pm++) = *pmatrix;
            }
            pmatrix++;
        }
    }
}

double cofactor(int n, double matrix[][n], int i, int j) {
    double m[n - 1][n - 1];
    minor(n, matrix, m, i, j);
    return (((i + j) % 2) ? -1 : 1) * determinant(n - 1, m);
}

double determinant(int n, double matrix[][n]) {
    if (n == 1) return matrix[0][0];
    double x = 0.0;
    for (int i = 0; i < n; i++) {
        x += matrix[i][0] * cofactor(n, matrix, i, 0);
    }
    return x;
}

void invert(int n, double matrix[][n], double inverse[][n], double det) {
    if (n == 1) {
        inverse[0][0] = 1.0 / matrix[0][0];
        return;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inverse[i][j] = cofactor(n, matrix, j, i) / det;
        }
    }
}
