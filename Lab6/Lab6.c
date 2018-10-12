#include <stdio.h>
#include <stdbool.h>

bool checkLegalInDirection(char board[26][26], int n, char row, char col, char colour, int deltaRow, int deltaCol) {
	row = row + deltaRow;
	col = col + deltaCol;
	if ( (row<0 || col<0 || row>=n || col>=n) || (board[(int) row][(int) col]==colour) || (board[(int) row][(int) col]=='U') ) {
		return false;
	} else {
		while(row>=0 && col>=0 && row<n && col<n) {
			row = row + deltaRow;
			col = col + deltaCol;
			if (board[(int) row][(int) col] == colour) {
				return true;
			} else if (board[(int) row][(int) col] == 'U') {
				return false;
			}
		}
		return false;
	}  
}

void changeBoard(char board[26][26], int row, int col, char colour, int deltaRow, int deltaCol) {
	char opposite='B';
	if (colour=='B') {
		opposite = 'W';
	}
	do {
		board[row][col]=colour;
		row+=deltaRow;
		col+=deltaCol;
	} while (board[row][col]==opposite);
}

void playMove(char board[26][26], int n) {
	int deltaRow, deltaCol;
	char type, row, column;
	bool legal=false, legalMove;
	printf("\nEnter a move:\n");
	scanf(" %c%c%c", &type, &row, &column);
	for(deltaRow=1;deltaRow>=-1;deltaRow--){
		for(deltaCol=1; deltaCol>=-1; deltaCol--){
			if (deltaRow!=0 || deltaCol!=0) {
				legalMove = checkLegalInDirection(board, n, row-97, column-97, type, deltaRow, deltaCol);
				if (legalMove) {
					legal = true;
					changeBoard(board, row-97, column-97, type, deltaRow, deltaCol);
				}
			}
		}
	}
	if (legal) {
		printf("Valid move.\n");
	}  
	else {
		printf("Invalid move.\n");
	}
}

bool positionInBounds(int n, char row, char col) {
	bool empty = false;
	if (n>(row-97) && n>(col-97)) {
		empty = true;
	} 
	return empty;
}

bool positionEmpty(char board[26][26], char row, char col) {
	bool inBounds = false;
	if (board[row-97][col-97]=='U') {
		inBounds = true;
	} 
	return inBounds;
}

void availableMoves(char board[26][26], int n, char type) {
	int deltaRow, deltaCol;
	char row, col;
	bool inBounds, empty, legal;
	printf("\nAvailable moves for %c:", type);
	for (row=97; row<(n+97); row++) {
		for (col=97; col<(n+97); col++) {
			inBounds = positionInBounds(n, row, col);
			empty = positionEmpty(board, row, col);
			if (inBounds && empty) {
				for (deltaRow=1; deltaRow>=-1; deltaRow--) {
					for(deltaCol=1;deltaCol>=-1;deltaCol--) {
						if ((deltaRow!=0)||(deltaCol!=0)) {
							legal = checkLegalInDirection(board, n, row-97, col-97, type, deltaRow, deltaCol);
							if (legal) {
								printf("\n%c%c", row, col);
							}
						}
					}
				}
			}
		}
	}
}

void configureBoard(char board[26][26]) {
	char type='a', row='a', column='a';
	printf("\nEnter board configuration:\n");
	while (type!='!' && row!='!' && column!='!') {
		scanf(" %c%c%c", &type, &row, &column);
		board[row-97][column-97] = type;
    }
}

void printBoard(char board[26][26], int n) {
	char letter;
	int row, column;
	printf("  ");
	for (column=0; column<n; column++){
		letter = column + 97;
		printf("%c", letter);
	}
	for (row=0; row<n; row++) {
		letter = row + 97;
		printf("\n%c ", letter);
		for (column=0; column<n; column++) {
			printf("%c", board[row][column]);
		}
	}
	printf("\n")
}

void initializeBoard(char board[26][26], int n) {
	int row, column;
	for (row=0; row<n; row++) {
		for (column=0; column<n; column++) {
			if ((row==column)&&(column==n/2||column==n/2-1)) {
				board[row][column]='W';
			} else if (((row==n/2)&&(column==n/2-1))||((row==n/2-1)&&(column==n/2))) {
				board[row][column]='B';
			} else {
				board[row][column]='U';
			}
		}
	}
}

int main(void) {
	int n;
	char board[26][26];
	printf("Enter the board dimension: ");
	scanf("%d", &n);
	initializeBoard(board, n);
	printBoard(board, n);
	configureBoard(board);
	printBoard(board, n);
	availableMoves(board, n, 'W');
	availableMoves(board, n, 'B');
	playMove(board, n);
	printBoard(board, n);
	printf("\n");
	return 0;
}