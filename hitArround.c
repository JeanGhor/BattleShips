#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GRID_SIZE 10
void print_opponent_grid(int**grid, int difficult)
{
    printf("\n    ");
    for (int i=0; i<10; i++)
    {
        printf("%c   ", (char)(65+i));
    }
    for(int i=1; i<10; i++)
    {
        printf("\n%d   ", i);
        for(int j=0; j<10; j++)
        {
            if(grid[i-1][j]==0||grid[i-1][j]==1)
            {
                printf("~   ");
            }
            else if(grid[i-1][j]==2)
            {
                printf("*   ");
            }
            else if(grid[i-1][j]==3)
            {
                if(difficult==0)
                {
                    printf("o   ");
                }
            else if(grid[i-1][j] == 4){
                printf("~   ");
            }
            else
            {
                printf("~   ");
            }
            }
        }
    }
    printf("\n%d  ", 10);
    for(int j=0; j<10; j++)
    {
        if(grid[9][j]==0||grid[9][j]==1)
        {
            printf("~   ");
        }
        else if(grid[9][j]==2)
        {
            printf("*   ");
        }
        else if(grid[9][j]==3)
        {
            if(difficult==0)
            {
                printf("o   ");
            }
            else
            {
                printf("~   ");
            }
        }
    }
}


void fire(int** grid, int i, int j) {
    // Simulate firing at a cell
    printf("Fired at (%d, %d)\n", i, j);
    grid[i][j] = 2; // Mark it as hit (for testing purposes)
}

bool isInBounds(int i, int j) {
    return (i >= 0 && i < GRID_SIZE && j >= 0 && j < GRID_SIZE);
}

bool checkAndFireVertical(int** grid, int startX, int startY, int i, int j) {
    if (grid[i][j] == 2 && isInBounds(i + 1, j) && grid[i + 1][j] == 2) {
        // Check above
        if (isInBounds(i - 1, j) && grid[i - 1][j] == 0) {
            fire(grid, i - 1, j); // Fire above
            return true;
        }
        // Check below
        if (isInBounds(i + 2, j) && grid[i + 2][j] == 0) {
            fire(grid, i + 2, j); // Fire below
            return true;
        }
    }
    return false;
}

bool checkAndFireHorizontal(int** grid, int startX, int startY, int i, int j) {
    if (grid[i][j] == 2 && isInBounds(i, j + 1) && grid[i][j + 1] == 2) {
        // Check left
        if (isInBounds(i, j - 1) && grid[i][j - 1] == 0) {
            fire(grid, i, j - 1); // Fire left
            return true;
        }
        // Check right
        if (isInBounds(i, j + 2) && grid[i][j + 2] == 0) {
            fire(grid, i, j + 2); // Fire right
            return true;
        }
    }
    return false;
}

bool hitAround(int** grid, int startX, int startY, int i, int j) {
    if (!isInBounds(i, j)) {
        return false; // Out of bounds
    }

    if (grid[i][j] == 2) {
        if (checkAndFireVertical(grid, startX, startY, i, j)) {
            return true; // A hit was made
        }
        if (checkAndFireHorizontal(grid, startX, startY, i, j)) {
            return true; // A hit was made
        }

        if(hitAround(grid, startX, startY, i + 1, j))
            return true ;
        else if( hitAround(grid, startX, startY, i - 1, j))
            return true;
        else if( hitAround(grid, startX, startY, i, j + 1)) 
            return true;                                        // Right
        else if( hitAround(grid, startX, startY, i, j - 1))
            return true;                                       // Left
    }
    return false;
}


int main() {
    // Create a 10x10 grid and initialize it
    int** grid = (int**)malloc(GRID_SIZE * sizeof(int*));
    for (int i = 0; i < GRID_SIZE; i++) {
        grid[i] = (int*)malloc(GRID_SIZE * sizeof(int));
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = 0; // Initialize all cells to 0 (hidden)
        }
    }
    print_opponent_grid(grid,"easy");
    // Simulate some hits (2) in the grid
    grid[5][5] = 2; // Hit
    grid[4][5] = 2; // Hit
    grid[1][5] = 0; // Hidden cell above
    grid[7][5] = 0; // Hidden cell below

    grid[3][3] = 2; // Another hit
    grid[3][4] = 2; // Another hit
    grid[3][2] = 0; // Hidden cell to the left
    grid[3][5] = 0; // Hidden cell to the right
    print_opponent_grid(grid,"easy");

    // Test the hitAround function starting from a hit cell
    printf("Testing hitAround from (5, 5):\n");
    hitAround(grid, 5, 5, 5,5);

    printf("Testing hitAround from (3, 3):\n");
    hitAround(grid, 3, 3, 3, 3);
    print_opponent_grid(grid,"easy");

    // Free allocated memory
    for (int i = 0; i < GRID_SIZE; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}


