#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <Methods.c>
#include <weapons.c>

void hardBot (int difficult){
    int weapons1[] = {3, 0, 0, 0};
    int weapons2[] = {3, 0, 0, 0};
    char player[20];
    printf("\nEnter your name: ");
    scanf("%s", &player);
    system("pause");
    system("cls");
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
    system("pause");
    system("cls");
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
    int gameover = 0;
    int count = 0;
    int** found = (int**) malloc (4 * sizeof(int*));
    for(int k = 0; k < 4; k++){
        found[k] = (int*) malloc (2 * sizeof(int));
    }
    for(int k = 0; k < 4; k++){
        for(int l = 0; l < 2; l++){
            found[k][l] = -1;
        }
    }
    while(gameover == 0)
    {
        play(grid2,grid1,weapons1,Boats2,difficult,player);
        system("pause");
        system("cls");
        if(check_win(grid2)==1)
        {
            printf("\nYou won, congrats!");
            gameover = 1;
            system("pause");
            system("cls");
            break;
        }
        if (hit == 0){
            if (weapons2[1] > 0 && Boats2[0][0] != -1 && Boats2[0][0] != -2){

                if (Boats2[0][0] / 10 == 9)
                    i = Boats2[0][0] / 10 - 1;
                else
                    i = Boats2[0][0] / 10;
                if (Boats2[0][0] % 10 == 9)
                    j = Boats2[0][0] % 10 - 1;
                else 
                    j = Boats2[0][0] % 10;
                SmokeScreenBot(grid2, weapons2, i, j);
            }
            else if (count >= 3  && weapons2[0] > 0 && i != 9 && j != 9){
                calculateProb(pTable, grid1);
                highestProb(pTable, index);
                i = index[0];
                j = index[1];
                if(RadarSweepBot(grid1, weapons2, i, j, found)){
                    found[0][0] = i;
                    found[0][1] = j;
                    found[1][0] = i;
                    found[1][1] = j + 1; 
                    found[2][0] = i + 1;
                    found[2][1] = j;
                    found[3][0] = i + 1;
                    found[3][1] = j + 1;
                    hit = 1;
                }
                count = 0;
            }
            else{
                calculateProb(pTable, grid1);
                highestProb(pTable, index);
                i = index[0];
                j = index[1];
                Fire(grid1, i, j);
                if (grid1[i][j] == 2){
                    store[0] = i;
                    store[1] = j;
                    hit = 1;
                }
                count++;
            }
        }
        else{
            int read = 1;
            if (!hit_or_miss(grid1, Boats1)){
                count = 0;
                if(found[0][0] != -1 && found[0][1] != -1 && read && !(grid1[found[0][0]][found[0][1]] == 2) && !(grid1[found[0][0]][found[0][1]] == 3)){
                    if (FireBot(grid1, found[0][0], found[0][1])){
                        i = found[0][0];
                        j = found[0][1];
                        store[0] = i;
                        store[1] = j;

                    }
                    found[0][0] = -1;
                    found[0][1] = -1;
                    read = 0;
                }
                if(found[1][0] != -1 && found[1][1] != -1 && read && !(grid1[found[1][0]][found[1][1]] == 2) && !(grid1[found[1][0]][found[1][1]] == 3)){
                    if (Fire(grid1, found[1][0], found[1][1])){
                        i = found[1][0];
                        j = found[1][1];
                        store[0] = i;
                        store[1] = j;
                    }
                    found[1][0] = -1;
                    found[1][1] = -1;
                    read = 0;
                }
                if(found[2][0] != -1 && found[2][1] != -1 && read && !(grid1[found[2][0]][found[2][1]] == 2) && !(grid1[found[2][0]][found[2][1]] == 3)){
                    if (Fire(grid1, found[2][0], found[2][1])){
                        i = found[2][0];
                        j = found[2][1];
                        store[0] = i;
                        store[1] = j;
                    }
                    found[2][0] = -1;
                    found[2][1] = -1;
                    read = 0;
                }
                if(found[3][0] != -1 && found[3][1] != -1 && read && !(grid1[found[3][0]][found[3][1]] == 2) && !(grid1[found[3][0]][found[3][1]] == 3)){
                    if (Fire(grid1, found[3][0], found[3][1])){
                        i = found[3][0];
                        j = found[3][1];
                        store[0] = i;
                        store[1] = j;
                    }
                    found[3][0] = -1;
                    found[3][1] = -1;
                    read = 0;
                }
                if(isInBounds(i, j - 1) && direction[0] && (grid1[i][j - 1] == 0 || grid1[i][j - 1] == 1 || grid1[i][j - 1] == 2 || grid1[i][j - 1] == 4) && read){
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
                weapons2[1]++;
                hit = 0;
                for(int i = 0; i < 4; i++){
                    direction[i] = 1;
                }
                calculateProb(pTable, grid1);
                highestProb(pTable, index);
                i = index[0];
                j = index[1];
                Fire(grid1, i, j);
                if (grid1[i][j] == 2){
                    store[0] = i;
                    store[1] = j;
                    hit = 1;
                }
                count++;
            }
        }
        print_opponent_grid(grid1, difficult);
        if(check_win(grid1) == 1){
            printf("You lost, better luck next time!");
            gameover=1; 
            system("pause");
            system("cls");
            break;
        }
        system("pause");
        system("cls");
    }
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
            if(grid[i-1][j]==0||grid[i-1][j]==1||grid[i-1][j]==4)
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
        if(grid[9][j]==0||grid[9][j]==1||grid[9][j]==4)
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

int hit_or_miss(int** grid, int** Boats){
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
        else{
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

