#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Fire.c"
#include "RadarSweep.c"
#include "SmokeScreen.c"
#include "Artillery.c"
#include "Torpedo.c"

int calculateProb(int** pTable,int** grid);
void highestProb(int** pTable, int* index);
void possibleDirection(int** grid, int* direction, int i, int j);

int hardBot (int** grid, int** fgrid, int* weapons, int** Boats)
{
    int** pTable =(int**)malloc(10*sizeof(int*)); /*allocating space for the probablity table, a matrix where*/
    for(int i = 0 ; i < 10 ; i++)                 /*we'll store the likeliness of a boat being on that square*/
        pTable[i]= (int*)malloc(10*sizeof(int));
    if(!calculateProb(pTable,grid))                //Note, writing the p table isn't always necessary, 
        printf("error in calculate table");         //the code should be modified to know whether or not calculate it
        return 1;
    printf("executed");
    for (int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            printf("%s ",grid[i][j]);
        }
        printf("\n");
    }
    return 0;
};

int calculateProb(int** pTable,int** grid)
{
    for (int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(grid[i][j]==0||grid[i][j]==1||grid[i][j]==4)//if the case is untouched     //the method will go over each case of the matrix and everytime a case can posess a boat of size 
            {                                                                              // 2 to 5, we will increment the pTable position of said boat starting from the crrent square to 
                int obstructedV=0;                                                              //to the rest of the matrix. After the end of the method, the case possessing the biggest number
                int obstructedH=0;                                                              // has the highest probability of housing a boat.
                for(int boat = 1; boat < 5 && i+boat < 10; boat++)
                {
                    if( (grid[i+boat][j]==1||grid[i+boat][j]==0||grid[i+boat][j]==4)&&!obstructedH) //check if a boat can be hidding
                    {
                        for(int z=0; z < boat + 1;z++)                                              
                            pTable[i+z][j]++; 
                    }
                    else                                                                             //if it can't be hidding, then a boat of superior sized can't be either
                        obstructedH=0;
                }            
                for(int boat = 1; boat < 5&&j+boat<10;boat++)
                {
                    if( (grid[i][j+boat]==1||grid[i][j+boat]==0 || grid[i][j+boat]==4)&&!obstructedV)
                    {
                        for(int z=0; z < boat + 1;z++)
                            pTable[i][j+z]++; 
                    }
                    else
                        obstructedV=0;
                }
            }
        }
    }
};


void highestProb(int** pTable, int* index){
    int maxi = pTable[0][0];
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(pTable[i][j] >= maxi){
                maxi = pTable[i][j];
                index[0] = i;
                index[1] = j;  
                index[2] = maxi;          
            }
        }
    }
}

void hitAround(int** pTable, int** grid, int i, int j, int* direction){
    possibleDirection(grid, direction, i, j);
    int size = 0;
    for(int k = 0; k < 4; k++){
        if (direction[k] == 1)
            size++;
    }
    int** correctDirection = (int**) malloc (size * sizeof(int*));
    for (int k = 0; k < size; k++){
        correctDirection[k] = (int*) malloc (2 * sizeof(int));
    }
    int index = 0;
    for(int k = 0; k < 4; k++){
        if (direction[k] == 1){
            switch (k)
            {
            case 0:
                correctDirection[index][0] = i - 1;
                correctDirection[index][1] =  j;
                break;
            case 1:
                correctDirection[index][0] = i;
                correctDirection[index][1] =  j + 1;
                break;
            case 2:
                correctDirection[index][0] = i + 1;
                correctDirection[index][1] =  j;
                break;
            case 3:
                correctDirection[index][0] = i;
                correctDirection[index][1] =  j - 1;
                break;
            default:
                break;
            }
            index++;
        }
    }
    int* position = (int*) malloc (2 * sizeof(int));
    int maxi = pTable[correctDirection[0][0]][correctDirection[0][1]];
    position[0] = correctDirection[0][0];
    position[1] = correctDirection[0][1];
    for(int k = 1; k < size; k++){
        if (pTable[correctDirection[k][0]][correctDirection[k][1]] > maxi){
            maxi = pTable[correctDirection[k][0]][correctDirection[k][1]];
            position[0] = correctDirection[k][0];
            position[1] = correctDirection[k][1];
        }
    }
    Fire(grid, position[0], position[1]);
    for(int k = 0; k < 4; k++){
        direction[k] = 1;
    }
}

void possibleDirection(int** grid, int* direction, int i, int j){
    if (!(i - 1 >= 0) || grid[i - 1][j] == 2 ||grid[i - 1][j] == 3)
        direction[0] = 0;
    if (!(j + 1 < 10) || grid[i][j + 1] == 2 || grid[i][j + 1] == 3)
        direction[1] = 0;
    if (!(i + 1 < 10) || grid[i + 1][j] == 2 || grid[i + 1][j] == 3)
        direction[2] = 0;
    if (!(j - 1 >= 0) || grid[i][j - 1] == 2 || grid[i][j - 1] == 3)
        direction[3] = 0;
}

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

int main()
{
    int* weapons = {0};
    int** grid =(int**) malloc (10 * sizeof(int*));
    int* index = (int*) malloc (3 * sizeof(int));
    int* direction = (int*) malloc (4 * sizeof(int));
    for(int i = 0 ; i < 10 ; i++)                
    {
        grid[i]= (int*)malloc(10*sizeof(int));
    }
    int** pTable =(int**)malloc(10*sizeof(int*)); /*allocating space for the probablity table, a matrix where*/
    for(int i = 0 ; i < 10 ; i++)                 /*we'll store the likeliness of a boat being on that square*/
        pTable[i]= (int*)malloc(10*sizeof(int));
    for (int i = 0; i < 10; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            grid[i][j]=0;
            pTable[i][j]=0;
        }
    }
    for (int i = 0; i < 3; i++){
        index[i] = 0;
    }
    for(int i = 0; i < 4; i++){
        direction[i] = 1;
    }
    for (int i = 0; i < 10; i++)        //intialize both matrix and make sure they work properly
    {
        for(int j = 0; j < 10; j++)
        {
            printf("%d ",grid[i][j]);
        }
        printf("\n");
    }    
    calculateProb(pTable,grid);
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++)
        {
            printf("%d ",pTable[i][j]);
        }
        printf("\n");
    } 
    highestProb(pTable, index);
    printf("%d %d %d", index[0], index[1], index[2]);
    print_opponent_grid(grid, 0);
    // Simulate some hits in the grid
    grid[5][5] = 2;  
    grid[4][5] = 0;
    grid[3][3] = 2; 
    grid[3][4] = 1;
    print_opponent_grid(grid, 0);

    // Test the hitAround function starting from a hit cell
    printf("\nTesting hitAround from (5, 5):\n");
    hitAround(pTable, grid, 5, 5, direction);

    printf("\nTesting hitAround from (3, 3):\n");
    hitAround(pTable, grid, 3, 3, direction);
    print_opponent_grid(grid, 0);

    // Free allocated memory
    for (int i = 0; i < 10; i++) {
        free(grid[i]);
        free(pTable[i]);
    }
    free(grid);
    free(pTable);
    free(index);
    free(direction);
    return 0;
}