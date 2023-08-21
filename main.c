#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(void) {
    int height, width;

    printf("Desired Width: ");
    scanf("%d", &width);

    printf("\nDesired Height: ");
    scanf("%d", &height);

    InitBoard(height, width);

    return 0;
}

void InitBoard(int height, int width) {
    int deadBoard[height][width];
    memset(deadBoard, 0, sizeof(deadBoard));

    for (int i; i < height; i++) {
        for (int j; j < width; j++) {
            printf("%d", deadBoard[i][j]);
        }
    }
}