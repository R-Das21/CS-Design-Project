#include <stdio.h>
#include <stdlib.h>
int check(int row, int col);
void flag(int row, int col);
void printGrid();
int checkWin();

char hiddenGrid[10][10]; //hidden array
char playerGrid[10][10]; //User array

int main() {
    char choice;
    int row;
    int col;

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            hiddenGrid[i][j] = '0'; //Filling initial hidden array with zeros
            playerGrid[i][j] = '*'; //Filling initial user array with stars
        }
    }

    srand(2); //Rand function seeding

    for(int i=0; i<10; i++) {

        row=rand() % 10;
        col=rand() % 10;

        hiddenGrid[row][col]='M';
        //filling hidden array with 10 random mines
    }

    //Incrementing cells adjacent to mines including diagonals 
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            if(hiddenGrid[i][j]=='M'){
                if((i-1)>-1) {
                    if (hiddenGrid[i-1][j] != 'M') {
                        hiddenGrid[i-1][j]++;   
                    }
                    if((j-1)>=0 && hiddenGrid[i-1][j-1]!='M'){
                        hiddenGrid[i-1][j-1]++; 
                    }
                    if ((j+1)<10 && hiddenGrid[i-1][j+1]!='M'){
                        hiddenGrid[i-1][j+1]++; 
                    }
                }

                if((j-1)>=0 && hiddenGrid[i][j-1]!='M'){
                    hiddenGrid[i][j-1]++;   
                }
                if((j+1)<10 && hiddenGrid[i][j+1]!='M'){
                    hiddenGrid[i][j+1]++;   
                }

                if((i+1)<10){
                    if(hiddenGrid[i+1][j]!='M') {
                        hiddenGrid[i+1][j]++;  
                    }
                    if((j-1)>=0 && hiddenGrid[i+1][j-1]!='M'){
                        hiddenGrid[i+1][j-1]++;   
                    }
                    if ((j+1)<10 && hiddenGrid[i+1][j+1]!='M'){
                        hiddenGrid[i+1][j+1]++; 
                    }
                }
            }
        }
    }

    while(checkWin() == 0){   //Runs game till win function returns true indicating a win 

        printGrid();    //Prints User promts
        printf("Enter 'c' for check cell, 'f' for flag cell.\n");
        printf("Enter command and cell row col: ");
        scanf("%c %d %d", &choice, &row, &col);  //Scans user inputs
        printf("\n");

        if(choice =='c'){ 
            if(check(row, col) == 0) { //Checks if a mine is hit indicating a loss
                printGrid();
                printf("You hit a mine, game over.");
                return 0;
            }
        }
        else if (choice =='f'){  
            flag(row,col);  
        }
    }

    if(checkWin() == 1){ //Win statement
        printf("Congratulations! You win!\n");
    }
}


void printGrid() {   
    int i;
    int j;

    for (i = 0; i<10; i++){
        for (j = 0; j<10; j++) {
            printf("%c  ", playerGrid[i][j]);   //prints player grid
        }
        printf("\n");
    }
    printf("\n");
}

int check(int row, int col){

    if(hiddenGrid[row][col]=='M'){
        playerGrid[row][col]='M';
        return 0; //player loses if player selectes mine occupied cell 
    }
    else if(hiddenGrid[row][col]=='0') {    
        playerGrid[row][col]='0';           

        //Recursive call of check funtion on all cells adjacent to zero with error check of user grid to prevent infinite looping
        if ((row+1)<10) {
            if (playerGrid[row+1][col+1] == '*' && hiddenGrid[row+1][col+1]!='M') {
                if ((col+1)<10) {
                    check(row+1, col+1);    
                }
            }
            if (playerGrid[row+1][col]=='*' && hiddenGrid[row+1][col]!='M') {
                check(row+1, col);      
            }
            if (playerGrid[row+1][col-1]=='*' && hiddenGrid[row+1][col-1]!='M') {
                if (col-1 >= 0) {
                    check(row+1, col-1);
                }
            }
        }

        if (playerGrid[row][col+1]=='*' && hiddenGrid[row][col+1]!='M') {
            if ((col+1)<10) {
                check(row, col+1); 
            }
        }
        if (playerGrid[row][col-1]=='*' && hiddenGrid[row][col-1]!='M') {
            if ((col-1)>=0) {
                check(row, col-1); 
            }
        }

        if((row-1)>=0) {
            if (playerGrid[row-1][col+1]=='*' && hiddenGrid[row-1][col+1]!='M') {
                if ((col+1)<10) {
                    check(row-1, col+1);    
                }
            }
            if (playerGrid[row-1][col]=='*' && hiddenGrid[row-1][col]!='M') {
                check(row-1, col);  
            }
            if (playerGrid[row-1][col-1]=='*' && hiddenGrid[row-1][col-1]!='M') {
                if ((col-1) >= 0) {
                    check(row-1, col-1);    
                }
            }
        }
    }
    else{
        playerGrid[row][col] = hiddenGrid[row][col]; //else case to reveal cell in case that value is not zero
    }
    return 1;   
}

void flag(int row, int col){        
    if(playerGrid[row][col] == '*'){    //replaces playergrid cell with 'F' for flagged cell
        playerGrid[row][col] = 'F';
    }
}

int checkWin(){ 

    int i;
    int j;
    //reads through both arrays and compares each non mine value, if all non mines revealed player wins
    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
            if(hiddenGrid[i][j] != 'M'){
                if(hiddenGrid[i][j] != playerGrid[i][j]){
                    return 0;   
                }
            }
        }
    }
    return 1; 
}

