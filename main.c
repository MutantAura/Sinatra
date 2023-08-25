#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include "main.h"

#define clear() printf("\033[H\033[J")

const int lifeChance = 20; // Percentage chance a tile starts the game alive.
const __useconds_t refreshTime = 250; // Time in ms per cycle refresh. 

int aliveNeighbours;
int isAlive;

int main(void) {

    int state1[rows][cols]; // To be evaluated.
    int state2[rows][cols]; // To be rendered, then assigned to state1.

    int i, j;
    
    // Seed RNG
    srand( (__uint32_t)time(0) );

    // Generate initial random canvas, dead is weighted.
   for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if ((rand() % 100) > lifeChance) {
                state1[i][j] = 0;
                continue;
            }
            state1[i][j] = 1;
        }
    }

    Render(state1, &state2[0][0]);

   while(1) {
        clear();
        
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

        // sleep for refreshTime
        usleep(refreshTime * 1000);
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

            if (isAlive) {
                printf("O");
            }
            else printf(" ");

            *(state1Ptr + i * cols + j) = renderState[i][j];
        }
        printf("\n");
    }
}