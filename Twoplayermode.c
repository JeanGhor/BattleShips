//Requires: Inputs should be in the form specified by the program
//Effects: Leads a two player mode game guided step by step
//Testing Startegy: every method called was tested individually,
//Then the code was tested using a trial and error approach.(play until an error was found then correct it)
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
    print_opponent_grid(grid2, difficult);
    addboat("carrier", 5, grid2, Boats2);
    addboat("battleship", 4, grid2, Boats2);
    addboat("destroyer", 3, grid2, Boats2);
    addboat("submarine", 2, grid2, Boats2);
    //system("pause");
   // system("cls");

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
