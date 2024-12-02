//Requires: nothing
//Effects: returns 0 if the location entered is out of the grid's boundaries, 
//returns 1 if the operation is successful (changes the corresponding cell's value to 2 if it's a hit and 3 if it's a miss)
int Fire(int** Grid, int row, int col){
    if (row > 9 || row < 0 || col > 9 || col < 0)
        return 0;
    if (Grid[row][col] == 1 || Grid[row][col] == 2 || Grid[row][col] == 4){ //Check if it contains a boat at this position
        printf("hit\n");
        Grid[row][col] = 2; //shot and hits a boat
    }
    else{
        printf("miss\n");
        Grid[row][col] = 3; //shot and miss a boat
    }
    return 1;
}

//Requires: the grid entered should be the opponent's grid while the
//array of weapons entered should belong to the current player
//Effects: reveals whether there are opponent ships in a 2x2 grid starting by the cell entered
//returns 0 if the coordinates are wrong or
//prints a message if the player cannot use the weapon anymore and returns 1 or
//prints a message if ships were found or not and returns 1
int RadarSweep(int** Grid, int weapons[], int row, int col){
    if( weapons[0] < 0 )
    {
        printf("You've already used all of your Radar Sweeps! Next player's turn...\n");
        return 1;
    }
    if(col < 0 | col + 1 > 9 | row < 0 | row + 1> 9 )
    {
        return 0; // returning 0 to let the main function know that the coordinates were wrong.
    }
    if(Grid[row][col]==1||Grid[row][col+1]==1||Grid[row+1][col]==1||Grid[row+1][col+1]==1) //checks if a ship is found
        printf("Enemy ships found!\n");//tells the use a ship has been spotted
    else
        printf("No enemy ships found.\n");
    weapons[0]--; //uses the weapons
    return 1;
}

//Requires: the grid entered should be the opponent's grid while the
//array of weapons entered should belong to the current player
//Effects: hides the hits of a 2x2 area by turning the corresponding cells' values to 4 in the grid
//prints a message if the player cannot use the weapon
//returns 0 if the coordinates are wrong 
//returns 1 if the operation is successful
int SmokeScreen(int** Grid, int* weapons, int row, int col){
    if(col < 0 | col + 1 > 9 | row < 0 | row + 1> 9 )
    {
        return 0; // returning 0 to let the main function know that the coordinates were wrong.
    }
    if(weapons[1]==0)
        printf("You can not use this weapon! Next player's turn...\n");
    else
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
    weapons[1]--;
    return 1; // the method was ran succesfuly.
}

int Artillery(int** Grid, int weapons[], int row, int col){
    if(weapons[2]==0)
    {
        printf("You can not use this weapon! Next player's turn...\n");
        return 1;
    }
    if(col < 0 | col + 1 > 9 | row < 0 | row + 1> 9 )
    {
        return 0; // returning 0 to let the main function know that the coordinates were wrong.
    }
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
        printf("hit\n");
    else
        printf("miss\n");
    return 1; // the method was ran succesfuly.
}

//Requires: the grid entered should be the opponent's grid while the
//array of weapons entered should belong to the current player
//the isrow should be entered as 1 if the target is a row and 0 if it is a column
//Effects: hits a whole row or column 
//prints a message if the weapon cannot be used
//returns 0 if the coordinates are wrong
//returns 1 if the operation is successful
int Torpedo(int** Grid, int weapons[], int isrow, int roworcolumn){
    if (weapons[3] == 3){ //check if they can play torpedo 
        weapons[3] = 0;
        if (roworcolumn < 0 || roworcolumn > 9)
            return 0;
        int count = 0; //we will us it to check if they hit a boat
        if(isrow){ //The row "roworcolumn" will be hit
            for(int i = 0; i < 10; i++){
                if (Grid[roworcolumn][i] == 1 || Grid[roworcolumn][i] == 4){ //checks if there is a boat in this row
                    Grid[roworcolumn][i] = 2; //shot and hits a boat
                    count++;
                }
                else
                    Grid[roworcolumn][i] = 3; //shot and miss a boat
            }
        }
        else{ //The column "roworcolumn" will be hit
            for(int i = 0; i < 10; i++){
                if (Grid[i][roworcolumn] == 1 || Grid[i][roworcolumn] == 4){ //checks if there is a boat in this column
                    Grid[i][roworcolumn] = 2; //shot and hit a boat
                    count++;
                }
                else
                    Grid[i][roworcolumn] = 3; //shot and miss a boat
            }
        }
        if (count > 0) //check if it hit a boat
            printf("hit\n");
        else
            printf("miss\n");
    }
    else{ //They can not play torpedo
        printf("You can not use this weapon! Next player's turn...\n");
    }
    return 1;
}