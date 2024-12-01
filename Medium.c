//Requires: Inputs should be in the form specified by the program
// A boat cannot start right after the cell where another boat finishes
//Effects: Leads a single player mode game against a medium level robot
void medium(int difficult){

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