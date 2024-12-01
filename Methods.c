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
//Requires: the grid entered should be the one of the player currently entering his boats
//Effects: prints a 10x10 grid with ~ for empty regions and * for regions with boats
void printgrid(int ** grid)
{
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
int position_boat(int** grid, int col, int row, char direction, int boat, int** Boats)
{
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
void addboat(char*boat, int cells, int**grid, int** Boats)
{
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
void print_opponent_grid(int**grid, int difficult)
{
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
    printf("\n");
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


