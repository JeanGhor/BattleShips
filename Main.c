#include <stdio.h>
#include <stdlib.h>
#include "Medium.c"
#include "Hard.c"
#include "easy.c"
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
else difficult=1;
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
    if(level==1)
    {
        easyBot(difficulty);
    }
    else if(level==2){
        medium(difficult);
    }
    else if(level==3)
    {
        hardBot(difficulty);
    }

}
}