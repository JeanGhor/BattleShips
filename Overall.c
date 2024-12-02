#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "weapons.c"
void printgrid(int** grid);
int position_boat(int** grid, int col, int row, char direction, int boat, int** Boats);
void addboat(char*boat, int cells, int**grid, int** Boats);
int check_win(int**grid);
void print_opponent_grid(int**grid, int difficult);
int hit_or_miss(int** grid, int** Boats);
int hit_or_miss2(int** grid, int** Boats);
int hit_or_miss3(int** grid, int** Boats, int* weapons);
void play(int** grid, int**fgrid, int* weapons, int** Boats, int difficult, char*player);
void highestProb(int** pTable, int* index);
int calculateProb(int** pTable,int** grid);
void SetUp(int x, int** templates);
void robot_position_boat_hard(int boat, int**Boats, int**grid,int *chosen);
void robot_position_boat(int boat, int**Boats, int**grid);
int robot_position_boat_helper(int** grid, int col, int row, char direction, int boat, int** Boats);
bool isInBounds(int i, int j);
int FireBot(int** Grid, int row, int col);
int ArtilleryBot(int** Grid, int weapons[], int row, int col);
int SmokeScreenBot(int** Grid, int* weapons, int row, int col);
int TorpedoBot(int** Grid, int weapons[], int isrow, int roworcolumn);
int RadarSweepBot(int** Grid, int weapons[], int row, int col,int**found);

//Requires: Inputs should be in the form specified by the program
//Effects: Leads a two player mode game guided step by step
void twoplayermode(int difficult){
// Create a grid for each player
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

    //Ask for the players' names
    char player1[20];
    char player2[20];
    printf("\nPlayer 1, enter your name: ");
    scanf("%s", &player1);
    getchar();
    printf("\nPlayer 2, enter your name: ");
    scanf("%s", &player2);
    getchar();
    char*firstplayer;
    char*secondplayer;
    //Choose randomly who will start
   
    int first= (rand()%2)+1;
    if(first==1)
    {
        printf("\n%s will start.", player1);
        firstplayer=player1;
        secondplayer=player2;
    }
    else 
    {
        printf("\n%s will start.", player2);
        firstplayer=player2;
        secondplayer=player1;
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
    
    print_opponent_grid(grid1, difficult);
    //Ask each player to enter all boats using addboat function
    addboat("carrier", 5, grid1, Boats1);
    addboat("battleship", 4, grid1, Boats1);
    addboat("destroyer", 3, grid1, Boats1);
    addboat("submarine", 2, grid1, Boats1);
    

    printf("\n%s, all your boats are positioned.\n%s, it is your turn to enter yours.", firstplayer, secondplayer);
    //system("pause");
    //system("cls");

    print_opponent_grid(grid2, difficult);
    addboat("carrier", 5, grid2, Boats2);
    addboat("battleship", 4, grid2, Boats2);
    addboat("destroyer", 3, grid2, Boats2);
    addboat("submarine", 2, grid2, Boats2);
    //system("pause");
    //system("cls");

    int weapons1[] = {3, 0, 0, 0};
    int weapons2[] = {3, 0, 0, 0};

    int gameover=0;
    while(gameover==0)
    {
        printf("%s, it's your turn.\n",firstplayer);
        play(grid2,grid1, weapons1, Boats2, difficult, firstplayer);
        if(check_win(grid2)==1){
            printf("%s won!", firstplayer);
            gameover=1;
            break;
        }
        //system("pause");
        //system("cls");

        printf("%s, it's your turn.\n",secondplayer);
        play(grid1,grid2, weapons2, Boats1, difficult, secondplayer);
        if(check_win(grid1)==1)
        {
            printf("%s won!", secondplayer);
            gameover=1;
            break;
        }
        //system("pause");
        //system("cls");
    }
}

//Requires: the user should follow the steps printed on the console
//Effects: leads a single player mode against a low level robot
void easyBot(int difficult){
    int weapons1[] = {3, 0, 0, 0};
    int weapons2[] = {3, 0, 0, 0};
    char player[20];
    printf("\nEnter your name: ");
    scanf("%s", &player);
    getchar();
    //system("pause");
    //system("cls");

    int**grid1=(int**)malloc(10*sizeof(int*));
    for(int i=0; i<10; i++){
        grid1[i]=(int*)malloc(10*sizeof(int));
    }
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            grid1[i][j]=0; 
        }
    }

    int**grid2=(int**)malloc(10*sizeof(int*));
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

    print_opponent_grid(grid1, difficult);
    addboat("carrier", 5, grid1, Boats1);
    addboat("battleship", 4, grid1, Boats1);
    addboat("destroyer", 3, grid1, Boats1);
    addboat("submarine", 2, grid1, Boats1);
    //system("pause");
    //system("cls");
    robot_position_boat(5, Boats2, grid2);
    robot_position_boat(4, Boats2, grid2);
    robot_position_boat(3, Boats2,  grid2);
    robot_position_boat(2, Boats2, grid2);

    int hit = 0;
    int* store = (int*) malloc (2 * sizeof(int));
    int* direction = (int*) malloc (4 * sizeof(int));
    for(int i = 0; i < 4; i++){
        direction[i] = 1;
    }
    int i;
    int j;
    int gameover = 0;
    while(gameover == 0){
        //system("pause");
        //system("cls");

        play(grid2,grid1, weapons1, Boats2, difficult, player);
        //system("pause");
        //system("cls");

        if(check_win(grid2)==1){
            printf("%s won!", player);
            gameover=1;
            break;
        }
        if (hit == 0){
            do{
                i = rand() % 10;
                j = rand() % 10;
            }while(grid1[i][j] == 2 || grid1[i][j] == 3);
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
            if (!hit_or_miss(grid1, Boats1)){
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
                do{
                    i = rand() % 10;
                    j = rand() % 10;
                }while(grid1[i][j] == 2 || grid1[i][j] == 3);
                printf("%d %d\n", i, j);
                Fire(grid1, i, j);
                if (grid1[i][j] == 2){
                    store[0] = i;
                    store[1] = j;
                    hit = 1;
                }
            }
        }
        print_opponent_grid(grid1, difficult);
        if(check_win(grid1) == 1){
            printf("You lost, better luck next time!");
            gameover=1; 
            break;
        }
    }
}

//Requires: Inputs should be in the form specified by the program
// A boat cannot start right after the cell where another boat finishes
//Effects: Leads a single player mode game against a medium level robot
void mediumBot(int difficult){

int weapons1[] = {3, 0, 0, 0};
int weapons2[] = {3, 0, 0, 3};
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

print_opponent_grid(grid1, difficult);
addboat("carrier", 5, grid1, Boats1);
addboat("battleship", 4, grid1, Boats1);
addboat("destroyer", 3, grid1, Boats1);
addboat("submarine", 2, grid1, Boats1);
//system("pause");
//system("cls");

robot_position_boat(5, Boats2, grid2);
robot_position_boat(4, Boats2, grid2);
robot_position_boat(3, Boats2,  grid2);
robot_position_boat(2, Boats2, grid2);

int i=0; 
int j=0;
int x=2;
int sunk=0;
int gameover=0;

while(gameover==0){
    //system("pause");
    //system("cls");
    play(grid2, grid1, weapons1, Boats1, difficult, player);
    //system("pause");
    //system("cls");
    if(check_win(grid2)==1){
        printf("You won, congrats!!");
        gameover=1;
        break;
    }

    Fire(grid1, i, j);
    print_opponent_grid(grid1, difficult);
    if(check_win(grid1)==1){
        printf("You lost, better luck next time!");
        gameover=1; 
        break;
    }


    if(grid1[i][j]==2){
        int visited=0;
        play(grid2, grid1, weapons1, Boats1, difficult, player);
        if(check_win(grid2)==1){
            printf("You won, congrats!!");
            gameover=1;
            break;
        }
        if(j-1>=0){
            Fire(grid1, i, j-1);
            print_opponent_grid(grid1, difficult);
            if(check_win(grid1)==1){
                printf("You lost, better luck next time!");
                gameover=1; 
                break;
            }
            if(grid1[i][j-1]==2){
                visited=1;
                if  (hit_or_miss2(grid1, Boats1)!=2){
                    play(grid2, grid1, weapons1, Boats1, difficult, player);
                    if(check_win(grid2)==1){
                        printf("You won, congrats!!");
                        gameover=1;
                        break;
                    }
        
                    Fire(grid1, i, j+1);
                    print_opponent_grid(grid1, difficult);
                    if(check_win(grid1)==1){
                        printf("You lost, better luck next time!");
                        gameover=1; 
                        break;
                    }
                    if(grid1[i][j+1]==2){
                        if(hit_or_miss2(grid1, Boats1)!=3){
                            play(grid2, grid1, weapons1, Boats1, difficult, player);
                            if(check_win(grid2)==1){
                                printf("You won, congrats!!");
                                gameover=1;
                                break;
                            }

                            Fire(grid1, i, j+2);
                            print_opponent_grid(grid1, difficult);
                            if(check_win(grid1)==1){
                                printf("You lost, better luck next time!");
                                gameover=1; 
                                break;
                            }
                        
                            if(grid1[i][j+2]==2 && hit_or_miss2(grid1, Boats1)!=4 ){
                                play(grid2, grid1, weapons1, Boats1, difficult, player);
                                if(check_win(grid2)==1){
                                    printf("You won, congrats!!");
                                    gameover=1;
                                    break;
                                }
                                Fire(grid1, i, j+3);
                                if(hit_or_miss2(grid1, Boats1)!=5){
                                    visited=0;
                                }
                                else {sunk++;
                                    if(sunk==3){
                                        play(grid2, grid1, weapons1, Boats1, difficult, player);
                                        if(check_win(grid2)==1){
                                            printf("You won, congrats!!");
                                            gameover=1;
                                            break;
                                        }
                                        Torpedo(grid1, weapons2, 1, 9);
                                        weapons2[3]=0;
                                        print_opponent_grid(grid1, difficult);
                                        if(check_win(grid1)==1){
                                            printf("You lost, better luck next time!");
                                            gameover=1; 
                                            break;
                                        }
                                    }
                                }
                                j+=2;
                                print_opponent_grid(grid1, difficult);
                                if(check_win(grid1)==1){
                                    printf("You lost, better luck next time!");
                                    gameover=1; 
                                    break;
                                }
                            } else {j+=2; sunk++;
                                    if(sunk==3){
                                        play(grid2, grid1, weapons1, Boats1, difficult, player);
                                        if(check_win(grid2)==1){
                                            printf("You won, congrats!!");
                                            gameover=1;
                                            break;
                                        }
                                        Torpedo(grid1, weapons2, 1, 9);
                                        weapons2[3]=0;
                                        print_opponent_grid(grid1, difficult);
                                        if(check_win(grid1)==1){
                                            printf("You lost, better luck next time!");
                                            gameover=1; 
                                            break;
                                        }
                                    }
                                }
                        }else {sunk++;
                                if(sunk==3){
                                    play(grid2, grid1, weapons1, Boats1, difficult, player);
                                    if(check_win(grid2)==1){
                                        printf("You won, congrats!!");
                                        gameover=1;
                                        break;
                                    }
                                    Torpedo(grid1, weapons2, 1, 9);
                                    weapons2[3]=0;
                                    print_opponent_grid(grid1, difficult);
                                    if(check_win(grid1)==1){
                                        printf("You lost, better luck next time!");
                                        gameover=1; 
                                        break;
                                    }
                                }
                            }
                    }else visited=0;  

                }else {x++; sunk++;
                        if(sunk==3){
                            play(grid2, grid1, weapons1, Boats1, difficult, player);
                            if(check_win(grid2)==1){
                                printf("You won, congrats!!");
                                gameover=1;
                                break;
                            }
                            Torpedo(grid1, weapons2, 1, 9);
                            weapons2[3]=0;
                            print_opponent_grid(grid1, difficult);
                            if(check_win(grid1)==1){
                                printf("You lost, better luck next time!");
                                gameover=1; 
                                break;
                            }
                        }
                    }
            }
        } 
        if(i-1>=0 && visited==0){
            Fire(grid1, i-1, j);
            print_opponent_grid(grid1, difficult);
            if(check_win(grid1)==1){
                printf("You lost, better luck next time!");
                gameover=1; 
                break;
            }
            if(grid1[i-1][j]==2){
                visited=1;
                if(hit_or_miss2(grid1, Boats1)!=2){
                    play(grid2, grid1, weapons1, Boats1, difficult, player);
                    if(check_win(grid2)==1){
                        printf("You won, congrats!!");
                        gameover=1;
                        break;
                    }    
                    Fire(grid1, i+1, j);
                    print_opponent_grid(grid1, difficult);
                    if(check_win(grid1)==1){
                        printf("You lost, better luck next time!");
                        gameover=1; 
                        break;
                    }
                    if(grid1[i+1][j]==2 ){
                        if(hit_or_miss2(grid1, Boats1)!=3){
                            play(grid2, grid1, weapons1, Boats1, difficult, player);
                            if(check_win(grid2)==1){
                                printf("You won, congrats!!");
                                gameover=1;
                                break;
                            }
                            Fire(grid1, i+2, j);
                            print_opponent_grid(grid1, difficult);
                            if(check_win(grid1)==1){
                                printf("You lost, better luck next time!");
                                gameover=1; 
                                break;
                            }
                            if(grid1[i+2][j]==2 && hit_or_miss2(grid1, Boats1)!=4){
                                play(grid2, grid1, weapons1, Boats1, difficult, player);
                                if(check_win(grid2)==1){
                                    printf("You won, congrats!!");
                                    gameover=1;
                                    break;
                                }
                                Fire(grid1, i+3, j);
                                if(hit_or_miss2(grid1, Boats1)!=5){
                                    visited=0;
                                } else {sunk++;
                                        if(sunk==3){
                                            play(grid2, grid1, weapons1, Boats1, difficult, player);
                                            if(check_win(grid2)==1){
                                                printf("You won, congrats!!");
                                                gameover=1;
                                                break;
                                            }
                                            Torpedo(grid1, weapons2, 1, 9);
                                            weapons2[3]=0;
                                            print_opponent_grid(grid1, difficult);
                                            if(check_win(grid1)==1){
                                                printf("You lost, better luck next time!");
                                                gameover=1; 
                                                break;
                                            }
                                        }
                                    }
                                print_opponent_grid(grid1, difficult);
                                if(check_win(grid1)==1){
                                    printf("You lost, better luck next time!");
                                    gameover=1; 
                                    break;
                                }
                            } else {sunk++;
                                    if(sunk==3){
                                        play(grid2, grid1, weapons1, Boats1, difficult, player);
                                        if(check_win(grid2)==1){
                                            printf("You won, congrats!!");
                                            gameover=1;
                                            break;
                                        }
                                        Torpedo(grid1, weapons2, 1, 9);
                                        weapons2[3]=0;
                                        print_opponent_grid(grid1, difficult);
                                        if(check_win(grid1)==1){
                                            printf("You lost, better luck next time!");
                                            gameover=1; 
                                            break;
                                        }
                                    }
                                }
                        }else{ 
                            if(sunk==3){
                                play(grid2, grid1, weapons1, Boats1, difficult, player);
                                if(check_win(grid2)==1){
                                    printf("You won, congrats!!");
                                    gameover=1;
                                    break;
                                }
                                Torpedo(grid1, weapons2, 1, 9);
                                weapons2[3]=0;
                                print_opponent_grid(grid1, difficult);
                                if(check_win(grid1)==1){
                                    printf("You lost, better luck next time!");
                                    gameover=1; 
                                    break;
                                }
                            }
                        }
                    }else {visited=0;}
                } else {x++; sunk++;
                        if(sunk==3){
                            play(grid2, grid1, weapons1, Boats1, difficult, player);
                            if(check_win(grid2)==1){
                                printf("You won, congrats!!");
                                gameover=1;
                                break;
                            }
                            Torpedo(grid1, weapons2, 1, 9);
                            weapons2[3]=0;
                            print_opponent_grid(grid1, difficult);
                            if(check_win(grid1)==1){
                                printf("You lost, better luck next time!");
                                gameover=1; 
                                break;
                            }
                        }
                    }

            }
        }
        if(j+1<=10 && visited==0){
            Fire(grid1, i, j+1);
            print_opponent_grid(grid1, difficult);
            if(check_win(grid1)==1){
                printf("You lost, better luck next time!");
                gameover=1; 
                break;
            }
            if(grid1[i][j+1]==2){
                visited=1;
                if(hit_or_miss2(grid1, Boats1)!=2){
                    
                    play(grid2, grid1, weapons1, Boats1, difficult, player);
                    if(check_win(grid2)==1){
                        printf("You won, congrats!!");
                        gameover=1;
                        break;
                    }
                    Fire(grid1, i, j+2);
                    print_opponent_grid(grid1, difficult);
                    if(check_win(grid1)==1){
                        printf("You lost, better luck next time!");
                        gameover=1; 
                        break;
                    }
                    if(grid1[i][j+2]==2){
                        if(hit_or_miss2(grid1, Boats1)!=3){
                            play(grid2, grid1, weapons1, Boats1, difficult, player);
                            if(check_win(grid2)==1){
                                printf("You won, congrats!!");
                                gameover=1;
                                break;
                            }
                            Fire(grid1, i, j+3);
                            print_opponent_grid(grid1, difficult);
                            if(check_win(grid1)==1){
                                printf("You lost, better luck next time!");
                                gameover=1; 
                                break;
                            }
                            if(grid1[i][j+3]==2 && hit_or_miss2(grid1, Boats1)!=4){
                            
                                play(grid2, grid1, weapons1, Boats1, difficult, player);
                                if(check_win(grid2)==1){
                                    printf("You won, congrats!!");
                                    gameover=1;
                                    break;
                                }
                                Fire(grid1, i, j+4);
                                if(hit_or_miss2(grid1, Boats1)!=5){
                                    visited=0;
                                } else {sunk++;
                                        if(sunk==3){
                                            play(grid2, grid1, weapons1, Boats1, difficult, player);
                                            if(check_win(grid2)==1){
                                                printf("You won, congrats!!");
                                                gameover=1;
                                                break;
                                            }
                                            Torpedo(grid1, weapons2, 1, 9);
                                            weapons2[3]=0;
                                            print_opponent_grid(grid1, difficult);
                                            if(check_win(grid1)==1){
                                                printf("You lost, better luck next time!");
                                                gameover=1; 
                                                break;
                                            }
                                        }
                                    }
                                print_opponent_grid(grid1, difficult);
                                if(check_win(grid1)==1){
                                    printf("You lost, better luck next time!");
                                    gameover=1; 
                                    break;
                                }
                                j+=4;
                            } else{j+=2; sunk++;
                                    if(sunk==3){
                                        play(grid2, grid1, weapons1, Boats1, difficult, player);
                                        if(check_win(grid2)==1){
                                            printf("You won, congrats!!");
                                            gameover=1;
                                            break;
                                        }
                                        Torpedo(grid1, weapons2, 1, 9);
                                        weapons2[3]=0;
                                        print_opponent_grid(grid1, difficult);
                                        if(check_win(grid1)==1){
                                            printf("You lost, better luck next time!");
                                            gameover=1; 
                                            break;
                                        }
                                    }
                                }
                        }else {j+=2; sunk++;
                                play(grid2, grid1, weapons1, Boats1, difficult, player);
                                if(check_win(grid2)==1){
                                    printf("You won, congrats!!");
                                    gameover=1;
                                    break;
                                }
                                Torpedo(grid1, weapons2, 1, 9);
                                print_opponent_grid(grid1, difficult);
                                if(check_win(grid1)==1){
                                    printf("You lost, better luck next time!");
                                    gameover=1; 
                                    break;
                                }
                            }
                    } else{ visited=0;}
                } else {x++; sunk++;
                        if(sunk==3){
                            play(grid2, grid1, weapons1, Boats1, difficult, player);
                            if(check_win(grid2)==1){
                                printf("You won, congrats!!");
                                gameover=1;
                                break;
                            }
                            Torpedo(grid1, weapons2, 1, 9);
                            weapons2[3]=0;
                            print_opponent_grid(grid1, difficult);
                            if(check_win(grid1)==1){
                                printf("You lost, better luck next time!");
                                gameover=1; 
                                break;
                            }
                        }
                    }

            }
        }
        if(i+1<=10 && visited==0){
            Fire(grid1, i+1, j);
            print_opponent_grid(grid1, difficult);
            if(check_win(grid1)==1){
                printf("You lost, better luck next time!");
                gameover=1; 
                break;
            }
            if(grid1[i+1][j]==2){
                visited=1;
                if(hit_or_miss2(grid1, Boats1)!=2){
                    play(grid2, grid1, weapons1, Boats1, difficult, player);
                    if(check_win(grid2)==1){
                        printf("You won, congrats!!");
                        gameover=1;
                        break;
                    }

                    Fire(grid1, i+2, j);
                    print_opponent_grid(grid1, difficult);
                    if(check_win(grid1)==1){
                        printf("You lost, better luck next time!");
                        gameover=1; 
                        break;
                    }
                    if(grid1[i+2][j]==2 && hit_or_miss2(grid1, Boats1)!=3){
                        play(grid2, grid1, weapons1, Boats1, difficult, player);
                        if(check_win(grid2)==1){
                            printf("You won, congrats!!");
                            gameover=1;
                            break;
                        }

                        Fire(grid1, i+3, j);
                        print_opponent_grid(grid1, difficult);
                        if(check_win(grid1)==1){
                            printf("You lost, better luck next time!");
                            gameover=1; 
                            break;
                        }
                        if(grid1[i+3][j]==2 && hit_or_miss2(grid1, Boats1)!=4){
                            play(grid2, grid1, weapons1, Boats1, difficult, player);
                            if(check_win(grid2)==1){
                                printf("You won, congrats!!");
                                gameover=1;
                                break;
                            }

                            Fire(grid1, i+4, j);
                             if(hit_or_miss2(grid1, Boats1)!=5){
                                visited=0;
                            } else {sunk++;
                                    if(sunk==3){
                                        play(grid2, grid1, weapons1, Boats1, difficult, player);
                                        if(check_win(grid2)==1){
                                            printf("You won, congrats!!");
                                            gameover=1;
                                            break;
                                        }
                                        Torpedo(grid1, weapons2, 1, 9);
                                        weapons2[3]=0;
                                        print_opponent_grid(grid1, difficult);
                                        if(check_win(grid1)==1){
                                            printf("You lost, better luck next time!");
                                            gameover=1; 
                                            break;
                                        }
                                    }
                                }
                            print_opponent_grid(grid1, difficult);
                            if(check_win(grid1)==1){
                                printf("You lost, better luck next time!");
                                gameover=1; 
                                break;
                            }
                        } else {sunk++;
                                if(sunk==3){
                                    play(grid2, grid1, weapons1, Boats1, difficult, player);
                                    if(check_win(grid2)==1){
                                        printf("You won, congrats!!");
                                        gameover=1;
                                        break;
                                    }
                                    Torpedo(grid1, weapons2, 1, 9);
                                    weapons2[3]=0;
                                    print_opponent_grid(grid1, difficult);
                                    if(check_win(grid1)==1){
                                        printf("You lost, better luck next time!");
                                        gameover=1; 
                                        break;
                                    }
                                }
                            }
                    }else{ sunk++;
                            if(sunk==3){
                                play(grid2, grid1, weapons1, Boats1, difficult, player);
                                if(check_win(grid2)==1){
                                    printf("You won, congrats!!");
                                    gameover=1;
                                    break;
                                }
                                Torpedo(grid1, weapons2, 1, 9);
                                weapons2[3]=0;
                                print_opponent_grid(grid1, difficult);
                                if(check_win(grid1)==1){
                                    printf("You lost, better luck next time!");
                                    gameover=1; 
                                    break;
                                }
                            }
                        }
                } else {x++; sunk++;
                        if(sunk==3){
                            play(grid2, grid1, weapons1, Boats1, difficult, player);
                            if(check_win(grid2)==1){
                                printf("You won, congrats!!");
                                gameover=1;
                                break;
                            }
                            Torpedo(grid1, weapons2, 1, 9);
                            weapons2[3]=0;
                            print_opponent_grid(grid1, difficult);
                            if(check_win(grid1)==1){
                                printf("You lost, better luck next time!");
                                gameover=1; 
                                break;
                            }
                        }
                    }
            }
                
        }
        
    }
    if(grid1[i][j+2]==2){
        j=j+2;
    }

    j=j+x;
    if(j==10 && x==2){
        i=i+1;
        j=1;
    }
    else if(j==11){
        i=i+1;
        j=0;
    }
    else if(j==10 && x==3){
        i=i+1;
        j=2;
    }
    else if(j==12){
        i=i+1;
        j=1;
    }
}
}

//Requires: the user should follow the steps printed on the console
//Effects: leads a single player mode against a high level robot
void hardBot (int difficult){
    int weapons1[] = {3, 0, 0, 0};
    int weapons2[] = {3, 0, 0, 0};
    char player[20];
    printf("\nEnter your name: ");
    scanf("%s", &player);
    getchar();
    //system("pause");
    //system("cls");

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
    //system("pause");
    //system("cls");

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
    int notUsedSS = 1;
    int maxrow=0;
    int maxcol=0;
    int torpedoTargetV;
    int torpedoTargetH;
    int savei;
    int savej;
    int dummy;
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
        //system("pause");
        //system("cls");

        play(grid2,grid1,weapons1,Boats2,difficult,player);
        //system("pause");
        //system("cls");

        if(check_win(grid2)==1)
        {
            printf("\nYou won, congrats!");
            gameover = 1;
            break;
        }
        else if (hit == 0){
            if (weapons2[1] > 0 && Boats2[0][0] != -1 && Boats2[0][0] != -2 && notUsedSS){
                printf("\nSmoke Screen\n");
                if (Boats2[0][0] / 10 == 9)
                    i = Boats2[0][0] / 10 - 1;
                else
                    i = Boats2[0][0] / 10;
                if (Boats2[0][0] % 10 == 9)
                    j = Boats2[0][0] % 10 - 1;
                else 
                    j = Boats2[0][0] % 10;
                SmokeScreenBot(grid2, weapons2, i, j);
                notUsedSS = 0;
            }
            else if (count >= 3  && weapons2[0] > 0 && i != 9 && j != 9){
                printf("\nRadar Sweep\n");
                calculateProb(pTable, grid1);
                highestProb(pTable, index);
                i = index[0];
                j = index[1];
                if (i == 9)
                    i--;
                if (j == 9)
                    j--;
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
                printf("\nFire\n");
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
            printf("\nsearch around\n");
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
                    if (FireBot(grid1, found[1][0], found[1][1])){
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
                    if (FireBot(grid1, found[2][0], found[2][1])){
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
                    if (FireBot(grid1, found[3][0], found[3][1])){
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
                weapons2[2]++;
                weapons2[3]++;
                hit = 0;
                for(int i = 0; i < 4; i++){
                    direction[i] = 1;
                }
                if(weapons2[3]==3)
                {
                    printf("\nTorpedo\n");
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
                    {
                        z=TorpedoBot(grid1,weapons2,1,torpedoTargetH);
                        if(z)
                        {
                            if(!hit_or_miss3(grid1,Boats1,weapons2))
                            {
                                hit=1;
                            }
                            for(int khalas = 0 ; khalas<10;khalas++)
                            {
                                if (grid1[torpedoTargetH][khalas]==2)
                                {
                                    j=torpedoTargetH;
                                    i=khalas;
                                    store[0]=i;
                                    store[1]=j;
                                    printf("\n\n\n\n\n %d %d", i,j);
                                }
                            }
                        }
                    }
                    else
                    {
                        z=TorpedoBot(grid1,weapons2,0,torpedoTargetV);
                        if(z)
                        {
                            if(!hit_or_miss3(grid1,Boats1,weapons2))
                            {
                                hit=1;
                            }
                            for(int khalas = 0 ; khalas<10;khalas++)
                            {
                                if (grid1[khalas][torpedoTargetV]==2)
                                {
                                    i=khalas;
                                    j=torpedoTargetV;
                                    printf("\n\n\n\n\n %d %d", i,j);
                                }
                            }
                        }
                    }
                    store[0]=i;
                    store[1]=j;
                    printf("\n \n \n \n %d \n \n \n \n",hit);
                }
                else if(weapons2[2]>0)
                {
                    printf("\nArtillery\n");
                    maxrow=0;
                    calculateProb(pTable,grid1);
                    for (int i =0; i<9;i++)
                    {
                        for (int j=0;j<9;j++)
                        {
                            dummy=pTable[i][j]+pTable[i+1][j]+pTable[i][j+1]+pTable[i+1][j+1];
                            if (dummy>maxrow)
                            {
                                maxrow=dummy;
                                savei=i;
                                savej=j;
                            }
                            dummy=0;
                        }
                    }
                    if(ArtilleryBot(grid1,weapons2,savei,savej))
                    {
                        hit=1;


                        if(grid1[savei][savej]==2)
                        {
                            found[0][0]=savei;
                            found[0][1]=savej;
                        }
                        if(grid1[savei+1][savej]==2)
                        {
                            found[1][0]=savei+1;
                            found[1][1]=savej;
                        }
                        if(grid1[savei][savej+1]==2)
                        {
                            found[2][0]=savei;
                            found[2][1]=savej+1;
                        }
                        if(grid1[savei+1][savej+1]==2)
                        {
                            found[3][0]=savei+1;
                            found[3][1]=savej+1;
                        }
                    }
                    else
                        hit=0;
                    for(int i = 0 ; i<4; i++)
                    {
                        if(found[i][0]!=-1)
                        {
                            store[0]=found[i][0];
                            store[1]=found[i][1];
                        }
                    }
                    i=store[0];
                    j=store[1];
                    dummy=0;
                    maxrow=0;
                    for(int i = 0 ; i<4; i++)
                    {
                        for(int j = 0 ; j<2;j++)
                        {
                            found[i][j]=-1;
                        }
                    }
                }
                else
                {
                    printf("\nFire\n");
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
}

//Requires: the grid entered should be the one of the player currently entering his boats
//Effects: prints a 10x10 grid with ~ for empty regions and * for regions with boats
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

//Requires: nothing
//Effects: returns 0 if the location is not available 
//and returns 1 if the operation is successful (turns the corresponding cells'value to 1 in the player's grid)
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

//Requires: the boat should be a string of the boat's name and cells should be the number of cells the boat needs to fit
//Effects: Prints a message to ask the corresponding player to insert the location of the corresponding boat
//and keeps calling the position_boat method until the location entered is right
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

//Requires: the grid entered should be the opponent's grid to check if the current player has won
//Effects: returns 0 if the player did not win yet and returns 1 if the player has sunk all the opponent's boats
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

//Requires: the grid entered should be the opponent's grid 
//the difficulty should be set at 1 for hard mode and 0 for easy mode
//Effects: prints the grid showing * for hits and o as misses for the easy mode
//does not show misses in hard mode
//does not show outcome if the cell was hidden by smoke screen
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

//Requires: the grid entered should be the opponent's one while the boats array should be the current player's
//Effects: returns the number of boats sunk
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

//Requires: the grid entered should be the opponent's grid, the boats array should be the current player's array
//Effects:  returns, if a boat was sunk in the last play, the number of cells the boat is made of
int hit_or_miss2(int** grid, int** Boats){
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
            return count;
        }
    }
    return 0;
}
//Requires: the grid entered should be the opponent's grid, the boats array should be the current player's array and the current player's weapons
//Effects:  returns, if a boat was sunk in the last play, how many boats were sunk, and adjusts weapons accordingly
//Testing Strategy: To test hit or miss, we try first an empty grid. After checking the normal behavior, we try it with
//a grid where one boat was hit, a grid where the last cell of a boat was hit and we try a grid where 
//the last cell of 2 boats were hit.

int hit_or_miss3(int** grid, int** Boats,int* weapons){
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

//Requires: the steps printed on the console should be followed just as stated
//Effects: scans the user's input, calls the corresponding method to perform the move and prints the move's outcome
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
    if(weapons[3]==3)
    {
        weapons[3]=0;
    }
    int sunk = hit_or_miss(grid, Boats);
    weapons[1] += sunk;
    weapons[3] += sunk;
    if(sunk > 0){
        weapons[2] = 1;
    }
    printf("\n%d boats were sunk", sunk);
    printf("\nNext player turn...");
}

//Requires: the parameters should be the opponent's probability table 
//and an array storing the indices of the cell with highest probability of containing a ship
//Effects: updates the array with new indices of the next cell with highest probabilty
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

//Requires: the probability table and the grid entered should be the opponent's ones
//Effects: fills the probability table with the probability of containing a ship for each cell
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

//Requires: an integer between 0 and 7 and a 2D array
//Effects: returns specific places to place boats through the templates array
void SetUp(int x, int** templates){
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
//Requires: the parameters should include the length of the boat, the array that stores the robot's boats and its grid and the choosen template's boat position
//Effects: positions the boat in the robot's grid in at predefined coordinates depending on the template
//Testing Strategy: We do not need to consider the possibility of the int boat being abnormal as we specify it
//in the caller method. Same principle for Boats and grid, they are the responsability of the main method.
void robot_position_boat_hard(int boat, int**Boats, int**grid, int *chosen){
    int col = chosen[0];
    int row = chosen[1];
    char direction = (chosen[2]==1) ? 'h' : 'v';
    int x=0;
    while (x == 0)
    {
        x = robot_position_boat_helper(grid, col, row, direction, boat, Boats);
    }   
}

//Requires: the parameters should include the length of the boat, the array that stores the robot's boats and its grid
//Effects: positions the boat in the robot's grid in a random location after checking it is right
void robot_position_boat(int boat, int**Boats, int**grid){

 int row, col, d;
    char direction;
    int x;

    do {
        row = rand() % 9;
        col = rand() % 9;
        d = rand() % 2 + 1;
        direction = (d == 1) ? 'h' : 'v';
        x = robot_position_boat_helper(grid, col, row, direction, boat, Boats);
    } while (x == 0);  
}

//Requires: nothing
//Effects: helps the robot_position_ boat by returning 0 if the location chosen is not available, and returns 1 if it is (after positioning the boat)
int robot_position_boat_helper(int** grid, int col, int row, char direction, int boat, int** Boats)
{
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
         for(int i=0; i<boat; i++){
        
            if(grid[row+i][col]==1){
            
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

//Requires: nothing
//Effects: returns true if the coordinate is within the grid's boundaries and false if not
bool isInBounds(int i, int j) {
    return (i >= 0 && i < 10 && j >= 0 && j < 10);
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
        twoplayermode(difficult);
    }
    else{
        int level;
        printf("How smart do you want your enemy to be? (Level 1, 2, or 3)\n");
        scanf("%d", &level);
        if(level==1){
            easyBot(difficult);
        }
        else if(level==2){
            mediumBot(difficult);
        }
        else{
            hardBot(difficult);
        }  
    }
}
