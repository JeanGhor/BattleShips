//Requires: the user should follow the steps printed on the console
//Effects: leads a single player mode against a low level robot
//Testing strategy: Test the boat with both difficulties with a trial and error approach
void easyBot(int difficult){
    int weapons1[] = {3, 0, 0, 0};
    int weapons2[] = {3, 0, 0, 0};
    char player[20];
    printf("\nEnter your name: ");
    scanf("%s", &player);
    getchar();
    system("pause");
    system("cls");
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
    system("pause");
    system("cls");
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
        
        play(grid2,grid1, weapons1, Boats2, difficult, player);
        system("pause");
        system("cls");
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
        system("pause");
        system("cls");
    }
}

//Requires: nothing
//Effects: returns true if the coordinate is within the grid's boundaries and false if not
//Testing startegy: pass in bounds and out of bounds coordinates
bool isInBounds(int i, int j) {
    return (i >= 0 && i < 10 && j >= 0 && j < 10);
}