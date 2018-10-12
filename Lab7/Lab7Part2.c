#include <stdio.h>
#include <stdbool.h>

void printBoard(char board[26][26], int n);
bool positionInBounds(int n, char row, char col);
bool checkLegalInDirection(char board[26][26], int n, char row, char col, char colour, int deltaRow, int deltaCol);
void flip(int n, char board[26][26], char colour, char row, char col, int deltaRow, int deltaCol);
void filpAllAfterLegal(int n, char board[26][26], char colour, char row, char col);
bool checkLegal(int n, char board[26][26], char row, char col, char colour);
bool haveMove(int n, char board[26][26], char colour);
void finalCompare(int n, char board[26][26], char colour, char diffColour);
int score(int n, char board[26][26], char colour, int i, int j);
void scoreBoard(int n, char board[26][26], int copy[26][26], char colour);
void changeBestMove(int n, char board[26][26], int copy[26][26], char colour);
bool strategyCorner(int n, char board[26][26], int i, int j);
bool strategyStar(int n, char board[26][26], int i, int j);
bool firstCircle (int n, char board[26][26], int i, int j);
bool secondCircle (int n, char board[26][26], int i, int j);
bool thirdCircle (int n, char board[26][26], int i, int j);


void printBoard(char board[26][26], int n) {
	int i, j;
	char firstRow, firstCol;
	firstRow = 'a';
	firstCol = 'a';
	printf("  ");
	for(i=0; i<n; i++) {
		printf("%c",firstRow);
		firstRow++;
	}
	printf("\n");
	for(i=0; i<n; i++) {
		printf("%c ", firstCol);
		firstCol++;
		for (j=0; j<n; j++)
			printf("%c",board[i][j]);
		printf("\n");   //print according to the array input row by row
	}
}

bool positionInBounds(int n, char row, char col) {
	if ((n>(row-'a'))&&(n>(col-'a')))   
		return true;
	else
		return false;   //return false when point is out of the n
}

bool checkLegalInDirection(char board[26][26], int n, char row, char col, char colour, int deltaRow, int deltaCol) {
	int i=row-'a', j =col-'a';
	int counter=0;
	i += deltaRow;
	j += deltaCol;
	if((i<0)||(j<0)||(i>=n)||(j>=n))
		return false;   //when the first move gets out of the boundary
	else if (board[i][j]==colour)
		return false;   //when the first move is the same color
	else if (board[i][j]=='-')
		return false;   //when the first move is unoccupied
	else {
		while((i>=0)&&(j>=0)&&(i<n)&&(j<n)) {
			i+=deltaRow;
			j+=deltaCol;
			if(board[i][j]==colour)
				return true;    //when the end of different colors is the same color
			else if(board[i][j]=='-')
				return false;   //when the end of different colors is unoccupied
			else
				counter++;  //counter does not work in lab 6, it is prepared for lab 7
		}
		return false;   //when gets out of the boundary
	}
}

void flip(int n, char board[26][26], char colour, char row, char col, int deltaRow, int deltaCol){
	char sameColour, diffColour;    //the function only flip and not judge whether the move is available or not
	if (colour == 'O') {
		sameColour = 'O';
		diffColour = 'X';
	} else if (colour == 'X') {	
		sameColour = 'X';
		diffColour = 'O';
	}
	int i, j;
	i = row - 'a';
	j = col - 'a';
	board[i][j] = colour;   //flip the origin move
	i+=deltaRow;
	j+=deltaCol;
	while (board[i][j]==diffColour) {
		board[i][j]=sameColour; //flip the following moves one by one
		i+=deltaRow;
		j+=deltaCol;
	}
}

void flipAllAfterLegal(int n, char board[26][26], char colour, char row, char col){
	int deltaRow, deltaCol;
	for (deltaRow=-1; deltaRow<=1; deltaRow++) {
		for (deltaCol=-1; deltaCol<=1; deltaCol++) {
			if (deltaRow!=0||deltaCol!=0){
				if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol) == true) {
					flip(n, board, colour, row, col, deltaRow, deltaCol);
				}
			}
		}
	}
}

bool checkLegal(int n, char board[26][26], char row, char col, char colour){
	bool legal = false;
	int deltaRow, deltaCol;
	if (positionInBounds(n, row, col)==false){
		return legal;
	}
	if (board[row-'a'][col-'a']!='-')
		return legal;
	for (deltaRow=-1; deltaRow<=1; deltaRow++) {
		for (deltaCol=-1;deltaCol<=1;deltaCol++) {
			if (deltaRow!=0||deltaCol!=0){
				if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol) == true){
					legal = true;
				}
			}
		}
	}
	return legal;
}

bool haveMove(int n, char board[26][26], char colour){
	char row, col;
	int deltaRow, deltaCol;
	bool haveMove = false;
	for(deltaRow=0; deltaRow<n; deltaRow++){
		for(deltaCol=0; deltaCol<n; deltaCol++){
			row = 'a' + deltaRow;
			col = 'a' + deltaCol;
			if (checkLegal(n, board, row, col, colour)==true){
				haveMove = true;
			}
		}
	}
	return haveMove;
}

void finalCompare(int n, char board[26][26], char colour, char diffColour){
	int i, j;
	int numColour = 0;
	int numDiffColour = 0;
	for (i=0; i<n; i++){
		for (j=0; j<n; j++){
			if (board[i][j]==colour)
				numColour++;
			else if(board[i][j]==diffColour)
				numDiffColour++;
		}
	}
	if (numColour>numDiffColour)
		printf("%c player wins.",colour);
	else if (numColour<numDiffColour)
		printf("%c player wins.",diffColour);
	else
		printf("Draw!");
}

int score(int n, char board[26][26], char colour, int i, int j){
	int score=0;
	char diffColour;
	int numRow, numCol;
	char row, col;
	bool legal = false;
	row = 'a' + i;
	col = 'a' + j;
	if (colour == 'O')
		diffColour ='X';
	if (colour == 'X')
		diffColour = 'O';
	int deltaRow, deltaCol;
	for (deltaRow=-1; deltaRow<=1; deltaRow++) {
		for (deltaCol=-1; deltaCol<=1; deltaCol++) {
			if(deltaRow!=0||deltaCol!=0) {
				if (checkLegalInDirection(board, n, row, col, colour, deltaRow, deltaCol)==true){
					legal = true;
					numRow = i;
					numCol = j;
					numRow += deltaRow;
					numCol += deltaCol;
					while (board[numRow][numCol] == diffColour){
						score ++;
						numRow += deltaRow;
						numCol += deltaCol;
					}
				}
			}
		}
	}
	if (legal == true) {
		if (firstCircle(n, board, i, j) == true){
			if (strategyCorner(n, board, i, j) == true)
				score+=1000;
			else if ((i = 1)||(i = n-2)||(j = 1)||(j = n-2))
				score-=100;
			else 
				score+=100;
		}
		else if (secondCircle(n, board, i, j) == true){
			if (strategyStar(n, board, i, j) == true)
				score-=1000;
			else
				score+=50;
		}
		else if (thirdCircle(n, board, i,j) == true){
			score+=50;
		}
    }
    else
        score = 0;
    return score;
}

void scoreBoard(int n, char board[26][26], int copy[26][26], char colour){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            copy[i][j]= 0 + score(n, board, colour, i, j);
        }
    }
}

void changeBestMove(int n, char board[26][26], int copy[26][26], char colour){
    scoreBoard(n, board, copy, colour);
    int bestI, bestJ;
    int i, j;
    int count = 0;
    int highScore = 0;
    char row, col;
    for(i=0; i<n; i++){
        for (j=0; j<n; j++){
            if ((copy[i][j]!= 0) && (count == 0) && (board[i][j] == '-')){
                count++;
                bestI = i;
                bestJ = j;
                highScore = copy[i][j];
            }
            else if ((copy[i][j]>highScore) && (board[i][j] == '-') && (copy[i][j]!= 0)){
                bestI = i;
                bestJ = j;
                highScore = copy[i][j];
            }
        }
    }
    row = 'a'+bestI;
    col = 'a'+bestJ;
    flipAllAfterLegal(n, board, colour, row, col);
    printf("Computer places %c at %c%c.\n", colour, row, col);
    printBoard(board, n);
}

bool firstCircle (int n, char board[26][26], int i, int j){
    bool correct = false;
    if ((i == 0)||(j == 0)||(i == n -1)||(j == n-1))
        correct = true;
    return correct;
}

bool secondCircle (int n, char board[26][26], int i, int j){
    bool correct = false;
    if((i == 1)||(j == 1)||(i == n -2)||(j == n-2))
        correct = true;
    return correct;
}

bool thirdCircle (int n, char board[26][26], int i, int j){
    bool correct = false;
    if((i ==2)||(j == 2)||(i == n -3)||(j == n -3))
        correct = true;
    return correct;
}

bool strategyCorner(int n, char board[26][26], int i, int j){
    bool correct = false;
    if (((i == 0)&&(j == 0))||((i == 0)&&(j == n-1))||((i == n-1)&&(j == 0))||((i == n-1)&&(j == n-1)))
        correct = true;
    return correct;
}

bool strategyStar(int n, char board[26][26], int i, int j){
    bool correct = false;
    if (((i == 1)&&(j == 1))||((i == 1)&&(j == n -2))||((i == n-2)&&(j == 1))||((i == n -2)&&(j == n -2)))
        correct = true;
    return correct;
}



int main(void){
    int n;
    char board[26][26];
    int i,j;
    int out = 0;
    char row, col;
    char colour, diffColour;
    int copy[26][26];
    printf("Enter the board dimension: ");
    scanf("%d",&n);
    
    
    for (i=0;i<n;i++){
        for (j=0;j<n;j++)
            board[i][j]='-';    //first set all the elements '-'
    }
    
    
    board[n/2-1][n/2-1] = 'O';
    board[n/2-1][n/2] = 'X';
    board[n/2][n/2-1] = 'X';
    board[n/2][n/2] = 'O';  //define array in the range of n
    
    for (i=0;i<n;i++) {
        for(j=0;j<n;j++) {
            copy[i][j]=0;
        }
    }
    
    printf("Computer plays (X/O) : ");
    scanf(" %c",&colour);
    printBoard(board, n);   //print the board out
    
    if (colour == 'O')
        diffColour = 'X';
    if (colour == 'X')
        diffColour = 'O';
    
    if (colour == 'O'){
        printf("Enter move for colour %c (RowCol): ", diffColour);
        scanf(" %c %c", &row, &col);
        if (checkLegal(n, board, row, col, diffColour) == false){
            printf("Invalid move.\n%c player wins.",colour);
            return 0;
        }
        else{
            board[row-'a'][col-'a']= diffColour;
            flipAllAfterLegal(n, board, diffColour, row, col);
            printBoard(board, n);
        }
    }
    
    
    
    while (out<1) {
        
        if (haveMove(n, board, colour)==true)
            
            changeBestMove(n, board, copy, colour);
            
        
        else{
            if (haveMove(n, board, diffColour)==true){
                printf("%c player has no valid move.\n",colour);
            }
            else{
                finalCompare(n, board, colour, diffColour);
                return 0;
            }
        }
       
        
        
        if (haveMove(n, board, diffColour)==true){
            printf("Enter move for colour %c (RowCol): ", diffColour);
            scanf(" %c %c", &row, &col);
            if (checkLegal(n, board, row, col, diffColour) == false){
                printf("Invalid move.\n%c player wins.",colour);
                return 0;
            }
            else{
                board[row-'a'][col-'a']= diffColour;
                flipAllAfterLegal(n, board, diffColour, row, col);
                printBoard(board, n);
            }
        }
        
        
        else{
            if (haveMove(n, board, colour)==true){
                printf("%c player has no valid move.\n", diffColour);
            }
            else{
                finalCompare(n, board, colour, diffColour);
                return 0;
            }
        }
    }
}