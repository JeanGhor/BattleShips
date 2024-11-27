void medium(int difficult){

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

print_opponent_grid(grid1, difficult);
addboat("carrier", 5, grid1, Boats1);
addboat("battleship", 4, grid1, Boats1);
addboat("destroyer", 3, grid1, Boats1);
addboat("submarine", 2, grid1, Boats1);

robot_position_boat(5, Boats2, grid2);
robot_position_boat(4, Boats2, grid2);
robot_position_boat(3, Boats2,  grid2);
robot_position_boat(2, Boats2, grid2);

int i=0; 
int j=0;
int x=2;
int gameover=0;

while(gameover==0){
    play(grid2, grid1, weapons1, Boats1, difficult, player);
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
                            j+=2;
                            print_opponent_grid(grid1, difficult);
                            if(check_win(grid1)==1){
                                printf("You lost, better luck next time!");
                                gameover=1; 
                                break;
                            }
                        } else j+=2;
                    }
                    }else visited=0;  

                }else x++;
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
                            }
                            print_opponent_grid(grid1, difficult);
                            if(check_win(grid1)==1){
                                printf("You lost, better luck next time!");
                                gameover=1; 
                                break;
                            }
                        }
                    }}else {visited=0;}
                } else x++;

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
                            }
                            print_opponent_grid(grid1, difficult);
                            if(check_win(grid1)==1){
                                printf("You lost, better luck next time!");
                                gameover=1; 
                                break;
                            }
                            j+=4;
                        } else{j+=2;}}else j+=2;
                    } else{ visited=0;}
                } else x++;

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
                            }
                            print_opponent_grid(grid1, difficult);
                            if(check_win(grid1)==1){
                                printf("You lost, better luck next time!");
                                gameover=1; 
                                break;
                            }
                        }
                    }
                } else x++;
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
}}

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
