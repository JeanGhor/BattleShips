int** SetUp(int x)// !!!!!!!!this function's array should be plased in the main!!!!!!!!!!
{
    int***Templates[8][5][3]={
        {
            {0,0,1}, //0 is vertical 1 is horizontal
            {2,2,0},
            {6,4,1},
            {9,7,0},
        },
        {
            {1,1,0}, //0 is vertical 1 is horizontal
            {3,3,1},
            {0,8,1},
            {8,2,1},
        },
        {
            {7,0,0}, //0 is vertical 1 is horizontal
            {4,3,1},
            {0,4,0},
            {9,1,1},
        },
        {
            {0,5,1}, //0 is vertical 1 is horizontal
            {6,2,0},
            {1,6,1},
            {5,0,1},
        },
        {
            {3,1,0}, //0 is vertical 1 is horizontal
            {8,5,1},
            {4,7,0},
            {0,2,1},
        },
        {
            {1,8,0}, //0 is vertical 1 is horizontal
            {5,2,1},
            {9,3,1},
            {0,0,1},
        },
        {
            {6,0,1}, //0 is vertical 1 is horizontal
            {2,6,0},
            {0,3,1},
            {9,8,0},
        },
        {
            {0,1,0}, //0 is vertical 1 is horizontal
            {6,4,1},
            {4,2,1},
            {7,7,0},
        }
    };
    return Templates[x];
    //you need to select the template in the main before calling the function.
}
void robot_position_boat_hard(int boat, int**Boats, int**grid,int *chosen)
{
    int col = chosen[0];
    int row = chosen[1];
    char direction = (chosen[2]==1) ? 'h' : 'v';
    int x=0;
    while (x == 0)
    {
        x = robot_position_boat_hard_helper(grid, col, row, direction, boat, Boats);
    }   
}

int robot_position_boat_hard_helper(int** grid, int col, int row, char direction, int boat, int** Boats)
{
    if(direction=='h' || direction=='H')
    {
        for(int i=0; i<boat; i++)
        {
            if(col+i>=10)
            {     
                return 0;
            }
        }
        for(int i=0; i<boat; i++)
        {
            if(grid[row][col+i]==1)
            {
                return 0;
            }
        }
        for(int i=0; i<boat; i++)
        {
            grid[row][col+i]=1;
            Boats[boat - 2][i] = row * 10 + col + i;
        }
        return 1;
    }
    else
    {
        for(int i=0; i<boat; i++)
        {
            if(row+i>=10)
            {
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
