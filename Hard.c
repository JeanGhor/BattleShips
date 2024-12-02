//Requires: the user should follow the steps printed on the console
//Effects: leads a single player mode against a high level robot
void hardBot (int difficult){
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
        play(grid2,grid1,weapons1,Boats2,difficult,player);
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