#include <stdio.h>
#include <stdlib.h>

int calculateProb(int** pTable,int** grid);

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

void hitAround(int** pTable, int** grid, int i, int j){
    
}

int main()
{
    int* weapons = {0};
    int** grid =(int**) malloc (10*sizeof(int*));
    int* index = (int*) malloc (3 * sizeof(int));
    for (int i = 0; i < 3; i++){
        index[i] = 0;
    }
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
    return 0;
}