#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANGE (long long) 100000000
#define DIVISOR 65536

int main(void)
{
    srand(time(NULL));
    clock_t begin, end;
    long long i;

    printf("Test in progress... ");

    begin = clock();
    for (i = 0; i < RANGE; i++) {
        double x1 = rand() / DIVISOR;
        double x2 = (rand() + 1) / DIVISOR;
        double plus = x1 + x2;
        double minus = x1 - x2;
        double multiply = x1 * x2;
        double divide = x1 / x2;
    }
    end = clock();

    double timeElapsed = (double) (end - begin) / CLOCKS_PER_SEC;
    double rate = RANGE / timeElapsed;
    printf("Finished.\n");
    printf("%lld loops were executed in %gs.\n", RANGE, timeElapsed);
    printf("Average rate: %.2e loops per second.\n", rate);

    return 0;
}
