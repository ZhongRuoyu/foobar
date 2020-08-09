#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Change the following numbers to modify conditions of the repeated experiment
#define RECURRENCECOUNT 1000000 // How many times the experiment is repeated
#define STEPCOUNT 25 // Number of steps for each repetition
#define ALLOWSTAYING 1 // If for each step, the point is allowed stay at the point: 1; if not: 0

void calculateresult(int *, int, int, int);
void printresult(int *, int, int, int);

int main(void) {
    srand(time(NULL));

    int x[2*STEPCOUNT + 1];
    for (int a = 0; a < 2*STEPCOUNT + 1; a++) {
        x[a] = 0; // Initialise the array
    }

    calculateresult(x, RECURRENCECOUNT, STEPCOUNT, ALLOWSTAYING);
    printresult(x, RECURRENCECOUNT, STEPCOUNT, ALLOWSTAYING);

    return 0;
}

void calculateresult(int *x, int recurrenceCount, int stepCount, int allowStaying) {
    for (int recurrence = 1; recurrence <= recurrenceCount; recurrence++) {
        int position = stepCount; // The initial position is set to the middle of the array
        for (int step = 0; step < stepCount; step++) {
            if (allowStaying) {
                int change = rand() % 3 - 1; // Range: {-1, 0, 1}
                position += change;
            } else {
                int forward = rand() % 2; // Range: {0, 1}
                if (forward) {
                    position += 1;
                } else {
                    position += -1;
                }
            }            
        }
        x[position]++; // Save the final position to the array
    }
}

void printresult(int *x, int recurrenceCount, int stepCount, int allowStaying) {
    printf("The experiment was repeated %d times.\n", recurrenceCount);
    printf("In each repetition, the point moved %d steps.\n", stepCount);
    if (allowStaying) {
        printf("For each step, the point was allowed to stay at the point.\n");
    } else {
        printf("For each step, the point was not allowed to stay at the point.\n");
    }
    printf("Copy the following text to Excel, and use the Text to Columns tool if necessary.\n\n");
    for (int position = - stepCount; position <= stepCount; position++) {
        printf("%d\t%d\n", position, x[position + stepCount]);
    }
    printf("\n\n");
}