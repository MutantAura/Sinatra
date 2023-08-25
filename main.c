#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "main.h"

#define clear() printf("\033[H\033[J")

int main(void) {
    int state1[rows][cols]; // To be evaluated.
    int state2[rows][cols]; // To be rendered, then assigned to state1.

    int i, j;

    srand( time(NULL) );

    // Generate initial random canvas.
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            state1[i][j] = rand() % 2;
        }
    }

    Render(state1, &state2[0][0]);

    while(1) {
        system("clear");
        
        // Evaluate state2 based on live cell neighbours.
        for (i = 0; i < rows; i++) {
            for (j = 0; j < cols; j++) {
                isAlive = state1[i][j];
                aliveNeighbours = EvaluateNeighbourCount(state1, i, j);

                if (isAlive) {
                    if (aliveNeighbours < 2) {
                        state2[i][j] = 0;
                    }

                    else if (aliveNeighbours == 2 || aliveNeighbours == 3) {
                        state2[i][j] = state1[i][j];
                    }

                    else {
                        state2[i][j] = 0;
                    }
                }

                else if (aliveNeighbours == 3) {
                    state2[i][j] = 1;
                }
            }
        }

        // Print next generation
        Render(state2, &state1[0][0]);

        // sleep for 1s
        sleep(0.25);
    }

    return 0;
}

int EvaluateNeighbourCount(int state[rows][cols], int currentRow, int currentCol) {
    int counter = 0;

    for (int i = currentRow - 1; i <= currentRow + 1; i++) {
        for(int j = currentCol - 1; j <= currentCol + 1; j++){
            // Check if the cell being checked is: 1. The same as itself. 2. Out of bounds.
            if ((i == currentRow && j == currentCol) || (i < 0 || j < 0) || (i >= rows || j >= cols)) {
                continue;
            }

            if (state[i][j]==1) {
                counter++;
            }
        }
    }

    return counter;
}

void Render(int renderState[rows][cols], int* state1Ptr) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            isAlive = renderState[i][j];

            if (!isAlive) {
                printf("0");
            }
            printf("1");

            *(state1Ptr + i * cols + j) = renderState[i][j];
        }
        printf("\n");
    }
}