
#include <stdio.h>
#include <stdlib.h>

int calculateProb(int** pTable,int** grid);
void highestProb(int** pTable, int* index);
void possibleDirection(int* direction, int i, int j);
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
    possibleDirection(direction, i, j);
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
}

void possibleDirection(int* direction, int i, int j){
    if (!(i - 1 >= 0 ))
        direction[0] = 0;
    if (!(j + 1 < 10))
        direction[1] = 0;
    if (!(i + 1 < 10))
        direction[2] = 0;
    if (!(j - 1 >= 0))
        direction[3] = 0;
}

int main()
{
    int* weapons = {0};
    int** grid =(int**) malloc (10 * sizeof(int*));
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
#include <stdio.h>
#include <stdlib.h>
#include "Positioning.c"
int check_win(int**grid);
int calculateProb(int** pTable,int** grid);
void fire(int**grid,int i,int j);
int hard (difficulty)
{
    int weapons1[] = {3, 0, 0, 0};
    int weapons2[] = {3, 0, 0, 0};
    char player[20];
    printf("\nEnter your name: ");
    scanf("%s", &player);
    getchar();
    int**grid1=(int**)malloc(10*sizeof(int));
    for(int i=0; i<10; i++)
    {
        grid1[i]=(int*)malloc(10*sizeof(int));
    }
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            grid1[i][j]=0; 
        }
    }
    int**grid2=(int**)malloc(10*sizeof(int));
    for(int i=0; i<10; i++)
    {
        grid2[i]=(int*)malloc(10*sizeof(int));
    }
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            grid2[i][j]=0; 
        }
    }

     int **Boats1 = (int**)malloc(4*sizeof(int));
    for(int i = 0; i < 4; i++){
        Boats1[i] = (int*)malloc(5*sizeof(int));
        Boats1[i][0] = 0;
    }
    int **Boats2 = (int**)malloc(4*sizeof(int));
    for(int i = 0; i < 4; i++){
        Boats2[i] = (int*)malloc(5*sizeof(int));
        Boats2[i][0] = 0;
    }
    addboat("carrier", 5, grid1, Boats1);
    addboat("battleship", 4, grid1, Boats1);
    addboat("destroyer", 3, grid1, Boats1);
    addboat("submarine", 2, grid1, Boats1);

    int z = rand()%(8+1);
    int* chosen=SetUp(z);
    robot_position_boat_hard(5, Boats2, grid2, chosen);
    robot_position_boat_hard(4, Boats2, grid2, chosen);
    robot_position_boat_hard(3, Boats2,  grid2, chosen);
    robot_position_boat_hard(2, Boats2, grid2, chosen);
    free(chosen);
    int* mostLikely = (int*)malloc(3*sizeof(int));
    mostLikely[0]=-1;
    mostLikely[1]=-1;
    mostLikely[2]=-1;
    int count; //count the number of turns without hits.
    while(1==1)
    {
        play(grid2,grid1,weapons1,Boats1,difficulty,play);
        if(check_win(grid2)==1)
        {
            printf("You won, congrats!");
            break;
        }
        if(mostLikely[0]+mostLikely[1]+mostLikely[2]>-1)
        {
            if (weapons2[2]>0){}
            else if(weapons2[3]>0){}
            else if(count>=3&&weapons2[1]>0){}//reset count
            else if(count>=3&&weapons2[0]>0){}//reset count
            else
            {
                int** pTable =(int**)malloc(10*sizeof(int*)); /*allocating space for the probablity table, a matrix where*/
                for(int i = 0 ; i < 10 ; i++)                 /*we'll store the likeliness of a boat being on that square*/
                    pTable[i]= (int*)malloc(10*sizeof(int));
                highestProb(pTable,mostLikely);
            } //compute p table and fund most probable cell

        }
        else //hit around, most likely will be initialized and reinitiliazed to -1 whenever we sink a ship
        {

        }
        //if you know there's a cell, then fire
        //else if you have weapon, use  them
        //else, use probability table
    }
    return 0;
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

int check_win(int**grid)
{
    for (int i = 0; i < 10; i++) 
    {
        for (int j = 0; j < 10; j++) 
        {
            if (grid[i][j] == 1 || grid[i][j] == 4) 
            {
                return 0;
            }
        }
    }
    return 1;
}
void play(int** grid, int**fgrid, int* weapons, int** Boats, int difficult, char*player){
    char String[100];
    char w;
    int row;
    int col;
    char c;
    char c1;
    char c2;
    int isrow ;
    int roworcolumn;
    print_opponent_grid(grid,difficult);
    do{
    printf("\nWhat would you like to do %s? (e.g. Fire C6):\n", player);
    printf("- Fire\n");
    if(weapons[0]>0)
        printf("- Radar Sweep\n");
    if(weapons[1]>0)
        printf("- Smoke Screen\n");
    if(weapons[2]>0)
        printf("- Artillery\n");
    if(weapons[3]==3)
        printf("- Torpedo (e.g. Torpedo A)\n");
    fgets(String, 20, stdin);
    w = String[0];
    }while(w != 'F' && w != 'R' && w != 'S' && w != 'A' && w != 'T');
    int size = 0;
    while(String[size + 1] != '\0'){
        size ++;
    }
    switch (w)
    {
    case 'F':
        if(String[size - 2] == '1' && String [size - 1]=='0')
        {
            c1 = String[size - 3];
            row = 9;
        }
        else
        {
            c1 = String[size - 2];
            c2 = String[size - 1];
            row = (int)(c2) - (int)('1');
        }
        col = (int)(c1) - (int)('A');
        if(Fire(grid, row, col) == 0)
            printf("Coordinates incorrect. Next player's turn... ");
        break;

    case 'R':
        if(String[size - 2] == '1' && String [size - 1]=='0')
        {
            c1 = String[size - 3];
            row = 9;
        }
        else
        {
            c1 = String[size - 2];
            c2 = String[size - 1];
            row = (int)(c2) - (int)('1');
        }
        col = (int)(c1) - (int)('A');
        if(RadarSweep(grid, weapons, row, col) == 0)
            printf("Coordinates incorrect. Next player's turn... ");
       break;
    
    case 'S':
        if(String[size - 2] == '1' && String [size - 1]=='0')
        {
            c1 = String[size - 3];
            row = 9;
        }
        else
        {
            c1 = String[size - 2];
            c2 = String[size - 1];
            row = (int)(c2) - (int)('1');
        }
        col = (int)(c1) - (int)('A');
        if(SmokeScreen(fgrid, weapons, row, col) == 0)
            printf("Coordinates incorrect. Next player's turn... ");
        break;

    case 'A':
        if(String[size - 2] == '1' && String [size - 1]=='0')
        {
            c1 = String[size - 3];
            row = 9;
        }
        else
        {
            c1 = String[size - 2];
            c2 = String[size - 1];
            row = (int)(c2) - (int)('1');
        }
        col = (int)(c1) - (int)('A');
        if(Artillery(grid, weapons, row, col) == 0)
            printf("Coordinates incorrect. Next player's turn... ");
        break;

    case 'T':
        c = String[size - 1];
        if(c=='0'&& String[size - 2]=='1')
        {
            row = 9;
        }
        else
        {
        col = (int)(c) - (int)('A');
        row = (int)(c) - (int)('1');
        }
        if (row >= 0 && row <=9){
                roworcolumn = row;
                isrow = 1;
            }
        if (col >= 0 && col <= 9){
            roworcolumn = col;
            isrow = 0;
        }
        if(Torpedo(grid, weapons, isrow, roworcolumn) == 0)
            printf("Coordinates incorrect. Next player's turn... ");
        break;
    
    default:
        break;
    }
    print_opponent_grid(grid, difficult);
    weapons[2] = 0;
    int sunk = hit_or_miss(grid, Boats);
    weapons[1] += sunk;
    weapons[3] += sunk;
    if(sunk > 0){
        weapons[2] = 1;
    }
    printf("\n%d boats were sunk", sunk);
    printf("\nNext player turn...");
}
int FireBot(int** Grid, int row, int col)
{
    if (Grid[row][col] == 1 || Grid[row][col] == 2 || Grid[row][col] == 4) //Check if it contains a boat at this position
    {
        printf("hit\n");
        Grid[row][col] = 2; //shot and hits a boat
        return 1;
    }
    else
    {
        printf("miss\n");
        Grid[row][col] = 3; //shot and miss a boat
        return 0;
    }
}
int ArtilleryBot(int** Grid, int weapons[], int row, int col)
{
    int hit = 0 ; 
    for(int i = 0 ; i < 2 ; i++)
        {
            for (int j = 0 ; j < 2 ; j++)
            {
                if(Grid[row+i][col+j]==1 || Grid[row+i][col+j]==4 || Grid[row+i][col+j]==2)
                {
                    Grid[row+i][col+j]=2; 
                    hit=1;
                }
                if (Grid[row+i][col+j]==0)
                    Grid[row+i][col+j]=3;
            }
        }
    if(hit)
        {
            printf("hit\n");
            return 1;
        }
    else
        {
            printf("miss\n");
            return 0;
        }
}
int SmokeScreen(int** Grid, int* weapons, int row, int col)
{
    for(int i = 0 ; i < 2 ; i++)
        {
            for (int j = 0 ; j < 2 ; j++)
            {
                if(Grid[row+i][col+j]==1)
                {
                    Grid[row+i][col+j]=4; // changes the tile to hide it from radar sweep
                }
            }
        }
}
int TorpedoBot(int** Grid, int weapons[], int isrow, int roworcolumn)
{
    int count = 0; //we will us it to check if they hit a boat
    if(isrow)
    { //The row "roworcolumn" will be hit
        for(int i = 0; i < 10; i++)
        {
            if (Grid[roworcolumn][i] == 1 || Grid[roworcolumn][i] == 4)
            { //checks if there is a boat in this row
                Grid[roworcolumn][i] = 2; //shot and hits a boat
                count++;
            }
            else
                Grid[roworcolumn][i] = 3; //shot and miss a boat
            }
    }
    else
    { //The column "roworcolumn" will be hit
        for(int i = 0; i < 10; i++)
        {
            if (Grid[i][roworcolumn] == 1 || Grid[i][roworcolumn] == 4)
            { //checks if there is a boat in this column
                Grid[i][roworcolumn] = 2; //shot and hit a boat
                count++;
            }
            else
                Grid[i][roworcolumn] = 3; //shot and miss a boat
        }
    }
    if (count > 0) //check if it hit a boat
    {
        printf("hit\n");
        return 1;
    }
    else
    {
        printf("miss\n");
        return 0;
    }
}
int RadarSweepBot(int** Grid, int weapons[], int row, int col,int**found)
{
    weapons[0]--; //uses the weapons
    if(Grid[row][col]==1||Grid[row][col+1]==1||Grid[row+1][col]==1||Grid[row+1][col+1]==1){ //checks if a ship is found
        printf("Enemy ships found!\n");//tells the use a ship has been spotted
        return 1;
    }
    else
    {
        printf("No enemy ships found.\n");
        return 0;
    }
}