#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Fire.c"
#include "RadarSweep.c"
#include "SmokeScreen.c"
#include "Artillery.c"
#include "Torpedo.c"

void printgrid(int** grid);
int position_boat(int** grid, int col, int row, char direction, int boat, int** Boats);
void addboat(char*boat, int cells, int**grid, int** Boats);
int check_win(int**grid);
void print_opponent_grid(int**grid, int difficult);
int hit_or_miss(int** grid, int** Boats,int*weapons);
void play(int** grid, int**fgrid, int* weapons, int** Boats, int difficult, char*player);
void highestProb(int** pTable, int* index);
int calculateProb(int** pTable,int** grid);
void SetUp(int x, int** templates);
void robot_position_boat_hard(int boat, int**Boats, int**grid,int *chosen);
int robot_position_boat_hard_helper(int** grid, int col, int row, char direction, int boat, int** Boats);
bool isInBounds(int i, int j);
int FireBot(int** Grid, int row, int col);
int ArtilleryBot(int** Grid, int weapons[], int row, int col);
int SmokeScreenBot(int** Grid, int* weapons, int row, int col);
int TorpedoBot(int** Grid, int weapons[], int isrow, int roworcolumn);
int RadarSweepBot(int** Grid, int weapons[], int row, int col,int**found);


int hardBot (int difficult){
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

    int z = rand() % 8;
    int** templates = (int**) malloc (4 * sizeof(int*));
    for(int i = 0; i < 4; i++){
        templates[i] = (int*) malloc (3 * sizeof(int));
    }
    SetUp(z, templates);
    robot_position_boat_hard(5, Boats2, grid2, templates[0]);
    robot_position_boat_hard(4, Boats2, grid2, templates[1]);
    robot_position_boat_hard(3, Boats2,  grid2, templates[2]);
    robot_position_boat_hard(2, Boats2, grid2, templates[3]);
    for(int i = 0; i < 4; i++){
        free(templates[i]);
    }
    free(templates);
    int** pTable = (int**) malloc (10 * sizeof(int*));
    for(int i = 0; i < 10; i++){
        pTable[i] = (int*) malloc (10 * sizeof(int));
    }
    int* index = (int*) malloc (3 * sizeof(int));
    int hit = 0;
    int* store = (int*) malloc (2 * sizeof(int));
    int* direction = (int*) malloc (4 * sizeof(int));
    for(int i = 0; i < 4; i++){
        direction[i] = 1;
    }
    int i;
    int j;
    int maxrow=0;
    int maxcol=0;
    int torpedoTargetV;
    int torpedoTargetH;

    int dummy;
    int gameover = 0;
    while(gameover == 0)
    {
        play(grid2,grid1,weapons1,Boats2,difficult,player);
        if(check_win(grid2)==1)
        {
            printf("\nYou won, congrats!");
            gameover = 1;
            break;
        }
        if (hit == 0){

                calculateProb(pTable, grid1);
                highestProb(pTable, index);
                i = index[0];
                j = index[1];
                printf("%d %d\n", i, j);
                Fire(grid1, i, j);
                if (grid1[i][j] == 2){
                   store[0] = i;
                   store[1] = j;
                    hit = 1;
                }
        }
        else{
            int read = 1;
            if (!hit_or_miss(grid1,Boats1,weapons2)){
                if(isInBounds(i, j - 1) && direction[0] && (grid1[i][j - 1] == 0 || grid1[i][j - 1] == 1 || grid1[i][j - 1] == 2 || grid1[i][j - 1] == 4)){
                    for(int k = 1; isInBounds(i, j - k) && grid1[i][j - k] != 3; k++){
                        if (grid1[i][j - k] != 2){
                            Fire(grid1, i, j - k);
                            read = 0;
                            break;
                        }
                    }
                }
                if(isInBounds(i - 1, store[1]) && direction[1] && (grid1[i - 1][store[1]] == 0 || grid1[i - 1][store[1]] == 1 || grid1[i - 1][store[1]] == 2 || grid1[i - 1][store[1]] == 4) && read){
                   direction[0] = 0;
                    for(int k = 1; isInBounds(i - k, j) && grid1[i - k][j] != 3; k++){
                        if (grid1[i - k][j] != 2){
                            Fire(grid1, i - k, j);
                            read = 0;
                            break;
                        }
                    }
                }
                if(isInBounds(store[0], j + 1) && direction[2] && (grid1[store[0]][j + 1] == 0 || grid1[store[0]][j + 1] == 1 || grid1[store[0]][j + 1] == 2 || grid1[store[0]][j + 1] == 4) && read){
                    direction[1] = 0;
                    for(int k = 1; isInBounds(i, j + k) && grid1[i][j + k] != 3; k++){
                        if (grid1[i][j + k] != 2){
                            Fire(grid1, i, j + k);
                            read = 0;
                            break;
                        }
                    }
                }
                if(isInBounds(i + 1, store[1]) && direction[3] && (grid1[i + 1][store[1]] == 0 || grid1[i + 1][store[1]] == 1 || grid1[i + 1][store[1]] == 2 || grid1[i + 1][store[1]] == 4) && read){
                   direction[2] = 0;
                    for(int k = 1; isInBounds(i + k, j) && grid1[i + k][j] != 3; k++){
                        if (grid1[i + k][j] != 2){
                            Fire(grid1, i + k, j);
                            break;
                        }
                    }
                }
            }
            else{
                hit = 0;
                for(int i = 0; i < 4; i++){
                    direction[i] = 1;
                }
                calculateProb(pTable, grid1);
                highestProb(pTable, index);
                i = index[0];
                j = index[1];
                printf("%d %d\n", i, j);
                if(weapons2[3]==3)
                {
                     for(int i=0;i<10;i++)
                    {
                         printf("\n");
                     }
                     for (int x=0;x<10;x++)
                     {
                        dummy=0;
                        for(int y=0;y<10;y++)
                        {
                           if (grid1[x][y]==0||grid1[x][y]==1||grid1[x][y]==4)
                               dummy++;
                        }   
                        if(maxrow<dummy)
                        {
                            maxrow=dummy;
                            torpedoTargetH=x;
                         }
                     }
                    for (int x=0;x<10;x++)
                    {
                        dummy=0;
                        for(int y=0;y<10;y++)
                        {
                            if (grid1[y][x]==0||grid1[y][x]==1||grid1[y][x]==4)
                                dummy++;
                       }
                        if(dummy>maxcol)
                        {
                            maxcol=dummy;
                            torpedoTargetV=x;
                        }
                    }
                    if(maxrow>maxcol)
                        TorpedoBot(grid1,weapons2,1,torpedoTargetH);
                    else
                        TorpedoBot(grid1,weapons2,0,torpedoTargetV);
                    }
                    else
                    {
                        Fire(grid1, i, j);
                        if (grid1[i][j] == 2){
                         store[0] = i;
                         store[1] = j;
                         hit = 1;
                    }
                }
            }
        }
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                printf("%d ", pTable[i][j]);
            }
            printf("\n");
        }
        print_opponent_grid(grid1, difficult);
        if(check_win(grid1) == 1){
            printf("You lost, better luck next time!");
            gameover=1; 
            break;
        }
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                pTable[i][j] = 0;
            }
        }
    }
    return 0;
}

void printgrid(int** grid){
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
            if(grid[i-1][j]==0)
            {
                printf("~   ");
            }
            else
            {
                printf("*   ");
            }
        }
    }
    printf("\n%d  ", 10);
    for(int j=0; j<10; j++)
    {
        if(grid[9][j]==0){
            printf("~   ");
        }
        else{
            printf("*   ");
        }
    }
    printf("\n");
}

int position_boat(int** grid, int col, int row, char direction, int boat, int** Boats){
    if(direction=='h' || direction=='H'){
        for(int i=0; i<boat; i++){
            if(col+i> (int)'K'-(int)'A'){
                printf("Location entered is wrong.");
                return 0;
            }
        }
         for(int i=0; i<boat; i++){
            if(grid[row][col+i]==1){
                printf("Location entered is wrong.");
                return 0;
            }
        }
        for(int i=0; i<boat; i++){
        grid[row][col+i]=1;
        Boats[boat - 2][i] = row * 10 + col + i;
        }
        return 1;
    }
    else{
        for(int i=0; i<boat; i++){
            if(row+i>10){
              printf("Location entered is wrong.");
              return 0;   
            }
        }
         for(int i=0; i<boat; i++){
            if(grid[row+i][col]==1){
              printf("Location entered is wrong.");
              return 0;   
            }
        }
        for(int i=0; i<boat; i++){
            grid[row+i][col]=1;
            Boats[boat - 2][i] = (row + i) * 10 + col;
        }
        return 1;
    }
}

void addboat(char*boat, int cells, int**grid, int** Boats){
    printf("\nEnter the first position of your %s (%d cells) and its direction \n(eg: B3, horizontal): ", boat, cells);
    char input[50];
    char * ptr=input;
    fgets(ptr, 50, stdin);
    char col=input[0];
    char row=input[1];
    int row2=(int)row-(int)'1';
    int col2=(int)col-(int)'A';
    char direction;
    if(row=='1' && input[2]=='0')
    {
        direction=input[5];
        row2=9;
    }
    else
    {
        direction=input[4];
    }
    int x=position_boat(grid, col2, row2, direction, cells, Boats);
    while(x!=1)
    {
        printf("\nEnter the first position of your %s (%d cells) and its direction \n(eg: B3, horizontal): ", boat, cells);
        fgets(ptr, 50, stdin);
        char col=input[0];
        char row=input[1];
        int row2=(int)row-(int)'1';
        int col2=(int)col-(int)'A';
        char direction;
        if(row=='1' && input[2]=='0')
        {
            direction=input[5];
            row2=9;
        }
        else
        {
            direction=input[4];
        }
        x=position_boat(grid, col2, row2, direction, cells, Boats);
    }
    printgrid(grid);
}

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

void print_opponent_grid(int**grid, int difficult){
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
    printf("\n");
}

int hit_or_miss(int** grid, int** Boats,int* weapons){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j<i+2; j++){  
            if(Boats[i][j]>=0)
            {
                if (grid[Boats[i][j] / 10][Boats[i][j] % 10] == 2)
                    Boats[i][j] = -1;
            }   
        }
    }
    int sunk = 0;
    for (int i = 0; i < 4; i++)
    {
        int count = 0;
        for (int j = 0; j < i + 2; j++)
        {
            if (Boats[i][j] == -1)
                count++;
        }
        if (count == i + 2)
        {
            sunk++;
            for (int j = 0; j < i + 2; j++){
                Boats[i][j] = -2;
            }
        }
        if(sunk)
        {
            weapons[1]++;
            weapons[2]++;
            weapons[3]++;
        }
        else
        {
            weapons[2]=0;
        }
    }
    return sunk;
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
    int sunk = hit_or_miss(grid, Boats,weapons);
    printf("\n%d boats were sunk", sunk);
    printf("\nNext player turn...");
}

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
            if(grid[i][j]==0||grid[i][j]==1||grid[i][j]==2||grid[i][j]==4)//if the case is untouched     //the method will go over each case of the matrix and everytime a case can posess a boat of size 
            {                                                                              // 2 to 5, we will increment the pTable position of said boat starting from the crrent square to 
            int obstructedV=0;                                                              //to the rest of the matrix. After the end of the method, the case possessing the biggest number
            int obstructedH=0;                                                              // has the highest probability of housing a boat.
            for(int boat = 1; boat < 5 && i+boat < 10; boat++)
                {
                    if( (grid[i+boat][j]==1||grid[i+boat][j]==0||grid[i][j+boat]==2||grid[i+boat][j]==4)&&!obstructedH) //check if a boat can be hidding
                    {
                        for(int z=0; z < boat + 1;z++)                                              
                            pTable[i+z][j]++; 
                    }
                    else                                                                             //if it can't be hidding, then a boat of superior sized can't be either
                        obstructedH=0;
                }            
            for(int boat = 1; boat < 5&&j+boat<10;boat++)
                {
                    if( (grid[i][j+boat]==1||grid[i][j+boat]==0||grid[i][j+boat]==2 || grid[i][j+boat]==4)&&!obstructedV)
                    {
                        for(int z=0; z < boat + 1;z++)
                            pTable[i][j+z]++; 
                    }
                    else
                        obstructedV=0;
                }
            }
        }
        for(int i = 0 ; i<10;i++)
        {
            for(int j =0;j<10;j++)
            {
                if(grid[i][j]==2||grid[i][j]==3)
                {
                    pTable[i][j]=0;
                }
            }
        }
    }
}

void SetUp(int x, int** templates){// !!!!!!!!this function's array should be plased in the main!!!!!!!!!!{
    if (x == 0){
        templates[0][0] = 0;
        templates[0][1] = 0;
        templates[0][2] = 1;
        templates[1][0] = 2;
        templates[1][1] = 2;
        templates[1][2] = 0;
        templates[2][0] = 6;
        templates[2][1] = 4;
        templates[2][2] = 1;
        templates[3][0] = 9;
        templates[3][1] = 7;
        templates[3][2] = 0;   
    }
    else if (x == 1){
        templates[0][0] = 1;
        templates[0][1] = 1;
        templates[0][2] = 0;
        templates[1][0] = 3;
        templates[1][1] = 3;
        templates[1][2] = 1;
        templates[2][0] = 0;
        templates[2][1] = 8;
        templates[2][2] = 1;
        templates[3][0] = 8;
        templates[3][1] = 2;
        templates[3][2] = 1;   
    }
    else if (x == 2){
        templates[0][0] = 7;
        templates[0][1] = 0;
        templates[0][2] = 0;
        templates[1][0] = 4;
        templates[1][1] = 3;
        templates[1][2] = 0;
        templates[2][0] = 0;
        templates[2][1] = 4;
        templates[2][2] = 1;
        templates[3][0] = 9;
        templates[3][1] = 1;
        templates[3][2] = 0;   
    }
    else if (x == 3){
        templates[0][0] = 0;
        templates[0][1] = 5;
        templates[0][2] = 1;
        templates[1][0] = 6;
        templates[1][1] = 2;
        templates[1][2] = 0;
        templates[2][0] = 1;
        templates[2][1] = 6;
        templates[2][2] = 1;
        templates[3][0] = 5;
        templates[3][1] = 0;
        templates[3][2] = 1;   
    }
    else if (x == 4){
        templates[0][0] = 3;
        templates[0][1] = 1;
        templates[0][2] = 0;
        templates[1][0] = 8;
        templates[1][1] = 5;
        templates[1][2] = 0;
        templates[2][0] = 4;
        templates[2][1] = 7;
        templates[2][2] = 0;
        templates[3][0] = 0;
        templates[3][1] = 2;
        templates[3][2] = 1;   
    }
    else if (x == 5){
        templates[0][0] = 1;
        templates[0][1] = 8;
        templates[0][2] = 1;
        templates[1][0] = 5;
        templates[1][1] = 2;
        templates[1][2] = 1;
        templates[2][0] = 9;
        templates[2][1] = 3;
        templates[2][2] = 0;
        templates[3][0] = 0;
        templates[3][1] = 0;
        templates[3][2] = 1;   
    }
    else if (x == 6){
        templates[0][0] = 8;
        templates[0][1] = 0;
        templates[0][2] = 0;
        templates[1][0] = 2;
        templates[1][1] = 6;
        templates[1][2] = 0;
        templates[2][0] = 0;
        templates[2][1] = 3;
        templates[2][2] = 1;
        templates[3][0] = 9;
        templates[3][1] = 8;
        templates[3][2] = 0;   
    }
    else if (x == 7){
        templates[0][0] = 0;
        templates[0][1] = 1;
        templates[0][2] = 0;
        templates[1][0] = 6;
        templates[1][1] = 4;
        templates[1][2] = 1;
        templates[2][0] = 4;
        templates[2][1] = 2;
        templates[2][2] = 1;
        templates[3][0] = 7;
        templates[3][1] = 7;
        templates[3][2] = 0;   
    }
}
void robot_position_boat_hard(int boat, int**Boats, int**grid, int *chosen){
    int col = chosen[0];
    int row = chosen[1];
    char direction = (chosen[2]==1) ? 'h' : 'v';
    int x=0;
    while (x == 0)
    {
        x = robot_position_boat_hard_helper(grid, col, row, direction, boat, Boats);
    }   
}

int robot_position_boat_hard_helper(int** grid, int col, int row, char direction, int boat, int** Boats){
    if(direction=='h' || direction=='H'){
        for(int i=0; i<boat; i++){
            if(col+i>=10){     
                return 0;
            }
        }
        for(int i=0; i<boat; i++){
            if(grid[row][col+i]==1){
                return 0;
            }
        }
        for(int i=0; i<boat; i++){
            grid[row][col+i]=1;
            Boats[boat - 2][i] = row * 10 + col + i;
        }
        return 1;
    }
    else{
        for(int i=0; i<boat; i++){
            if(row+i>=10){
              return 0;   
            }
        }
        for(int i=0; i<boat; i++)
        {
            if(grid[row+i][col]==1)
            {
                return 0;   
            }
        }
        for(int i=0; i<boat; i++)
        {
            grid[row+i][col]=1;
            Boats[boat - 2][i] = (row + i) * 10 + col;
        }
        return 1;
    }
}

bool isInBounds(int i, int j) {
    return (i >= 0 && i < 10 && j >= 0 && j < 10);
}

int FireBot(int** Grid, int row, int col){
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
int ArtilleryBot(int** Grid, int weapons[], int row, int col){
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
int SmokeScreenBot(int** Grid, int* weapons, int row, int col){
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
int TorpedoBot(int** Grid, int weapons[], int isrow, int roworcolumn){
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
int RadarSweepBot(int** Grid, int weapons[], int row, int col,int**found){
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

int main(){
    srand(time(NULL));
    char difficulty[5];
    char easy[]="easy";
    char hard[]="hard";
    printf("\nLet's play! Enter the difficulty level (easy/hard): ");
    scanf("%s", &difficulty);
    getchar();
    int difficult;
    if(strcmp(difficulty, easy)==0){
        difficult=0;
    }
    else 
        difficult=1;
    int numberplayers;
    printf("How many players are playing? (Enter 1 or 2)\n");
    scanf("%d", &numberplayers);
    if(numberplayers==2){
        //twoplayermode(difficult);
    }
    else{
        int level;
        printf("How smart do you want your enemy to be? (Level 1, 2, or 3)\n");
        scanf("%d", &level);
        if(level==1){
            //easyBot(difficult);
        }
        else if(level==2){
            //medium(difficult);
        }
        else{
            hardBot(difficult);
        }
    
    }
}