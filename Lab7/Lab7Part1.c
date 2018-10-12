#include <stdio.h>
#include <stdbool.h>

void initializeBoard(char board[][26], int scoreKeeper[][26], int n) {
	int row, column;
	for (row=0; row<n; row++) {
		for (column=0; column<n; column++) {
			scoreKeeper[row][column] = 0;
			if ((row==column)&&(column==n/2||column==n/2-1)) {
				board[row][column]='O';
			} else if (((row==n/2)&&(column==n/2-1))||((row==n/2-1)&&(column==n/2))) {
				board[row][column]='X';
			} else {
				board[row][column]='-';
			}
		}
	}
}

void printBoard(char board[][26], int n) {
	printf("  ");
	for (int column=0; column<n; column++)
		printf("%c", column+97);
	for (int row=0; row<n; row++) {
		printf("\n%c ", row+97);
		for (int column=0; column<n; column++) {
			printf("%c", board[row][column]);
		}
	}
	printf("\n");
}

bool positionInBounds(int n, char row, char col) {
	bool empty = false;
	if (n>(row-97) && n>(col-97)) {
		empty = true;
	} 
	return empty;
}

bool checkLegalInDirection(char board[][26], int n, char row, char col, char colour, int deltaRow, int deltaCol) {
	row = row + deltaRow;
	col = col + deltaCol;
	if (row<0 || col<0 || row>=n || col>=n || board[(int) row][(int) col]==colour || board[(int) row][(int) col]=='-')
		return false;
	else {
		while((row>=0)&&(col>=0)&&(row<n)&&(col<n)) {
			row = row + deltaRow;
			col = col + deltaCol;
			if(board[(int) row][(int) col]==colour)
				return true;
			else if(board[(int) row][(int) col]=='-')
				return false;
		}
		return false;
	}
}

void changeBoard(char board[][26], char row, char col, char colour, char opposite, int deltaRow, int deltaCol) {
	do {
		board[(int) row][(int) col]=colour;
		row = row + deltaRow;
		col = col + deltaCol;
	} while (board[(int) row][(int) col]==opposite);
}

void playMove(int n, char board[][26], char colour, char opposite, char row, char col) {
	for (int deltaRow=1; deltaRow>=-1; deltaRow--) {
		for (int deltaCol=1; deltaCol>=-1; deltaCol--) {
			if ((deltaRow!=0||deltaCol!=0)&&(checkLegalInDirection(board, n, row-97, col-97, colour, deltaRow, deltaCol) == true))
				changeBoard(board, row-97, col-97, colour, opposite, deltaRow, deltaCol);
		}
	}
}

bool legality(int n, char board[][26], char row, char col, char colour) {
	int deltaRow, deltaCol;
	if (positionInBounds(n, row, col)==false || board[row-'a'][col-'a']!='-')
		return false;
	for (deltaRow=1; deltaRow>=-1; deltaRow--) {
		for (deltaCol=1; deltaCol>=-1; deltaCol--) {
			if ((deltaRow!=0||deltaCol!=0)&&(checkLegalInDirection(board, n, row-97, col-97, colour, deltaRow, deltaCol) == true))
				return true;
		}
	}
	return false;
}

bool isMoveAvailable(int n, char board[][26], char colour){
	char row, column;
	for (int deltaRow=0; deltaRow<n; deltaRow++) {
		for (int deltaCol=0; deltaCol<n; deltaCol++) {
			row = deltaRow + 97;
			column = deltaCol + 97;
			if (legality(n, board, row, column, colour)==true)
				return true;
		}
	}
	return false;
}

void gameOver(int n, char board[][26], char computerColour, char playerColour) {
	int computerScore = 0, playerScore = 0;
	for (int row=0; row<n; row++) {
		for (int col=0; col<n; col++) {
			if (board[row][col]==playerColour)
				playerScore++;
			else if (board[row][col]==computerColour)
				computerScore++;
		}
	}
	if (computerScore==playerScore)
		printf("Draw!\n");
	else if (computerScore>playerScore)
		printf("%c player wins.\n", computerColour);
	else if (playerScore>computerScore)
		printf("%c player wins.\n", playerColour);
}

int scoreCount(int n, char board[][26], char colour, char opposite, int i, int j) {
	int rowNumber, columnNumber, deltaRow, deltaCol, scoreCounter=0;
	char row=i+97, col=j+97;
	for (deltaRow=-1; deltaRow<=1; deltaRow++) {
		for (deltaCol=-1; deltaCol<=1; deltaCol++) {
			if (deltaRow!=0||deltaCol!=0) {
				if (checkLegalInDirection(board, n, row-97, col-97, colour, deltaRow, deltaCol)==true){
					rowNumber = i + deltaRow;
					columnNumber = j + deltaCol;
					while (board[rowNumber][columnNumber]==opposite) {
						scoreCounter++;
						rowNumber = rowNumber + deltaRow;
						columnNumber = columnNumber + deltaCol;
					}
				}
			}
		}
	}
	return scoreCounter;
}

void findHighestScoringMove(int n, char board[][26], int scoreKeeper[][26], char computerColour, char playerColour) {
	int deltaRow, deltaCol, smartestRow, smartestCol, counter=0, smartestScore=0;
	char row, column;
	for(deltaRow=0; deltaRow<n; deltaRow++) {
		for (deltaCol=0; deltaCol<n; deltaCol++) {
			scoreKeeper[deltaRow][deltaCol] = scoreCount(n, board, computerColour, playerColour, deltaRow, deltaCol);
			if (counter==0 && board[deltaRow][deltaCol]=='-' && scoreKeeper[deltaRow][deltaCol]>0) {
				smartestRow = deltaRow;
				smartestCol = deltaCol;
				smartestScore = scoreKeeper[deltaRow][deltaCol];
				counter++;
			} else if (board[deltaRow][deltaCol]=='-' && smartestScore<scoreKeeper[deltaRow][deltaCol]) {
				smartestRow = deltaRow;
				smartestCol = deltaCol;
				smartestScore = scoreKeeper[deltaRow][deltaCol];
			}
		}
	}
	row = smartestRow + 97;
	column = smartestCol + 97;
	playMove(n, board, computerColour, playerColour, row, column);
	printf("Computer places %c at %c%c.\n", computerColour, row, column);
}

void playerTurn(int n, char board[][26], char computerColour, char playerColour, bool *exit) {
	char row, column;
	if (isMoveAvailable(n, board, playerColour)==true) {
		printf("Enter move for colour %c (RowCol): ", playerColour);
		scanf(" %c%c", &row, &column);
		if (legality(n, board, row, column, playerColour) == false) {
			printf("Invalid move.\n%c player wins.\n", computerColour);
			*exit = true;
		} else {
			board[row-97][column-97]= playerColour;
			playMove(n, board, playerColour, computerColour, row, column);
			printBoard(board, n);
		}
	} else if (isMoveAvailable(n, board, computerColour)==true)
			printf("%c player has no valid move.\n", playerColour);
	else {
		gameOver(n, board, computerColour, playerColour);
		*exit = true;
	}
}

void computerTurn(int n, char board[][26], char computerColour, char playerColour, int temp[26][26], bool *exit) {
	if (isMoveAvailable(n, board, computerColour)==true) {
		findHighestScoringMove(n, board, temp, computerColour, playerColour);
		printBoard(board, n);
	} else if (isMoveAvailable(n, board, playerColour)==true)
		printf("%c player has no valid move.\n", computerColour);
	else {
		gameOver(n, board, computerColour, playerColour);
		*exit = true;
	}
}

int main(void) {
	int n, scoreKeeper[26][26];
	bool exit=false;
	char board[26][26], row, column, computerColour, playerColour='O';
	printf("Enter the board dimension: ");
	scanf("%d", &n);
	initializeBoard(board, scoreKeeper, n);
	printf("Computer plays (%c/%c) : ", 'X', 'O');
	scanf(" %c", &computerColour);
	printBoard(board, n);
	if (computerColour == 'O') {
		playerColour = 'X';
		printf("Enter move for colour %c (RowCol): ", playerColour);
		scanf(" %c%c", &row, &column);
		if (legality(n, board, row, column, playerColour) == false) {
			printf("Invalid move.\n%c player wins.\n", computerColour);
			return 0;
		} else {
			board[row-97][column-97] = playerColour;
			playMove(n, board, playerColour, computerColour, row, column);
			printBoard(board, n);
		}
	}
	while (1) {
		computerTurn(n, board, computerColour, playerColour, scoreKeeper, &exit);
		if (exit == true)
			return 0;
		playerTurn(n, board, computerColour, playerColour, &exit);
		if (exit == true)
			return 0;
	}
}