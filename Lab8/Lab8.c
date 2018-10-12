//
// APS105 Lab 8 Lab8.c
//
// This is a program written to maintain a personal music library, 
// using a linked list to hold the songs in the library.
//
// Author: Syed Taimur Hassan
// Student Number: 1004278907
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// A node in the linked list

// Each string in the node is declared as a character pointer variable,
// so they need to be dynamically allocated using the malloc() function,
// and deallocated using the free() function after use.

typedef struct node {
	char *artist ;
	char *songName ;
	char *genre ;
	struct node *nextNode ;
} Node;

// Declarations of linked list functions
//
// DECLARE YOUR LINKED-LIST FUNCTIONS HERE
//

bool duplicateSong(Node *head, char songName[]);
Node *insertSong(Node *head, char son[], char art[], char gen[]);
void printLibrary(Node *head);
void searchLibrary(Node *head, char son[]);
Node *deleteSong(Node *head, char son[]);
void emptyLibrary(Node *head);

// Declarations of support functions
// See below the main function for descriptions of what these functions do

void inputStringFromUser( char prompt[], char s[], int arraySize ) ;
void songNameDuplicate( char songName[] ) ;
void songNameFound( char songName[] ) ;
void songNameNotFound( char songName[] ) ;
void songNameDeleted( char songName[] ) ;
void artistFound( char artist[] ) ;
void artistNotFound( char artist[] ) ;
void printMusicLibraryEmpty( void ) ;
void printMusicLibraryTitle( void ) ;

const int MAX_LENGTH = 1024;

int main( void ) {
	// Declare the head of the linked list.
	//   ADD YOUR STATEMENT(S) HERE
	Node *head = NULL;

	// Announce the start of the program
	printf( "Personal Music Library.\n\n" ) ;
	printf( "%s", "Commands are I (insert), D (delete), S (search by song name),\n"
		"P (print), Q (quit).\n" ) ;
    
	char response ;
	char input[ MAX_LENGTH + 1 ] ;
	do {
		inputStringFromUser( "\nCommand", input, MAX_LENGTH ) ;
		
		// Response is the first character entered by user.
		// Convert to uppercase to simplify later comparisons.
		response = toupper( input[0] ) ;
		
		if( response == 'I' ) {
			// Insert a song into the linked list.
			// Maintain the list in alphabetical order by song name.
			//   ADD STATEMENT(S) HERE
			char *promptName = "Song name", inputName[MAX_LENGTH + 1];
			char *promptArtist =  "Artist", inputArtist[MAX_LENGTH + 1];
			char *promptGenre = "Genre", inputGenre[MAX_LENGTH + 1];
			inputStringFromUser(promptName, inputName, MAX_LENGTH);
			inputStringFromUser(promptArtist, inputArtist, MAX_LENGTH);
			inputStringFromUser(promptGenre, inputGenre, MAX_LENGTH);
			if (duplicateSong(head, inputName) == true)
				songNameDuplicate(inputName);
			else
				head = insertSong(head, inputName, inputArtist, inputGenre);
			
			// USE THE FOLLOWING STRINGS WHEN PROMPTING FOR DATA:
			//    char *promptName = "Song name" ;
			//    char *promptArtist =  "Artist" ;
			//    char *promptGenre = "Genre" ;
			
		}
		else if( response == 'D' ) {
			// Delete a song from the list.
			
			char *prompt = "\nEnter the name of the song to be deleted" ;
			
			//   ADD STATEMENT(S) HERE
			char songToDelete[MAX_LENGTH + 1];
			inputStringFromUser(prompt, songToDelete, MAX_LENGTH);
			if (duplicateSong(head, songToDelete) == true) {
				songNameDeleted(songToDelete);				
				head = deleteSong(head, songToDelete);
			} else
				songNameNotFound(songToDelete);
		}
		else if( response == 'S' ) {
			// Search for a song by its name.
			
			char *prompt = "\nEnter the name of the song to search for" ;
			
			//   ADD STATEMENT(S) HERE
			char songToSearch[MAX_LENGTH + 1];
			inputStringFromUser(prompt, songToSearch, MAX_LENGTH);
			if (duplicateSong(head, songToSearch) == true)
				searchLibrary(head, songToSearch);
			else
				songNameNotFound(songToSearch);			
		}
		else if( response == 'P' ) {
			// Print the music library.
			
			//   ADD STATEMENT(S) HERE
			printLibrary(head);
			
		}
		else if( response == 'Q' ) {
			; // do nothing, we'll catch this below
		}
		else {
			// do this if no command matched ...
			printf( "\nInvalid command.\n" ) ;
		}
	} while( response != 'Q' ) ;
	
	// Delete the entire linked list.
	//   ADD STATEMENT(S) HERE
	emptyLibrary(head);
	
	// Print the linked list to confirm deletion.
	//   ADD STATEMENT(S) HERE
	printMusicLibraryEmpty();
	
	return 0 ;
}

// Support Function Definitions

// Prompt the user for a string safely, without buffer overflow
void inputStringFromUser(char prompt[], char s[], int maxStrLength) {
	int i = 0;
	char c;
	
	printf( "%s --> ", prompt ) ;
	while( i < maxStrLength && (c = getchar()) != '\n' )
		s[i++] = c ;
	s[i] = '\0' ;
}

// Function to call when the user is trying to insert a song name 
// that is already in the personal music library.
void songNameDuplicate( char songName[] ) {
	printf( "\nA song with the name '%s' is already in the music library.\n"
			"No new song entered.\n", songName);
}

// Function to call when a song name was found in the personal music library.
void songNameFound( char songName[] ) {
	printf( "\nThe song name '%s' was found in the music library.\n",
		songName ) ;
}

// Function to call when a song name was not found in the personal music library.
void songNameNotFound( char songName[] ) {
	printf( "\nThe song name '%s' was not found in the music library.\n",
		songName);
}

// Function to call when a song name that is to be deleted
// was found in the personal music library.
void songNameDeleted( char songName[] ) {
	printf( "\nDeleting a song with name '%s' from the music library.\n",
		songName);
}

// Function to call when printing an empty music library.
void printMusicLibraryEmpty(void) {
	printf( "\nThe music library is empty.\n" ) ;
}

// Function to call to print a title when the entire music library is printed.
void printMusicLibraryTitle(void) {
	printf( "\nMy Personal Music Library: \n" ) ;
}

// Add your functions below this line.

//   ADD STATEMENT(S) HERE

//The following the function searches the link list for a songName matching the given string, returns true if found
bool duplicateSong(Node *head, char songName[]) {
	Node *current = head;
	if (head) {
		while (current != NULL) {
			if (strcmp(current -> songName, songName) == 0)
				return true;
			current = current -> nextNode;
		}
		return false;
	} else
	return false;
}

//The following function adds a song to the linked list, in a position keeping the list in alphabetical order
Node *insertSong(Node *head, char inputSong[], char inputArtist[], char inputGenre[]) {
	Node *songToInsert = (Node *) malloc(sizeof (Node));
	songToInsert -> songName = (char *) malloc(MAX_LENGTH * sizeof(char));
	songToInsert -> artist = (char *) malloc(MAX_LENGTH * sizeof(char));
	songToInsert -> genre = (char *) malloc(MAX_LENGTH * sizeof(char));
	strcpy(songToInsert -> songName, inputSong);
	strcpy(songToInsert -> artist, inputArtist);
	strcpy(songToInsert -> genre, inputGenre);
	Node *current = head;
	Node *previousNode = head;
	if (!head)
		head = songToInsert;
	else if (strcmp(head -> songName, songToInsert -> songName) > 0) {
		head = songToInsert;
		head -> nextNode = current;
	} else {
		current = current -> nextNode;
		while (current != NULL) {
			if (strcmp(songToInsert->songName, current->songName) > 0) {
				previousNode = previousNode -> nextNode;
				current = current -> nextNode;
			} else {
				previousNode -> nextNode = songToInsert;
				songToInsert -> nextNode = current; 
				return head;
			}
		}
		previousNode -> nextNode = songToInsert;
		songToInsert -> nextNode = current;
    }
	return head;
}

//The following function prints the entire music libray, or prints an error message if the library is empty
void printLibrary(Node *head) {
	Node *current = head;
	if (head) {
		printMusicLibraryTitle();
		while (current != NULL) {
			printf("\n%s\n%s\n%s\n", current -> songName, current -> artist, current -> genre);
			current = current -> nextNode;
		}
	} else
		printMusicLibraryEmpty();
}

//The following searches the library for a song matching the given string, and prints the song info if found
void searchLibrary(Node *head, char songToSearch[]) {
	Node *current = head;
	while (current != NULL) {
		if (strcmp(current -> songName, songToSearch) == 0) {
			songNameFound(songToSearch);
			printf("\n%s\n%s\n%s\n", songToSearch, current -> artist, current -> genre);
			break;
		} else
			current = current -> nextNode;
	}
}

//The following function deletes a given song from the music library, and frees the memory allocated
Node *deleteSong(Node *head, char songToDelete[]) {
	Node *current = head;
	Node *temp;
	if (strcmp(head-> songName, songToDelete) == 0) {
	    temp = head;
		head = head -> nextNode;
		free(temp -> songName);
		free(temp -> artist);
		free(temp -> genre);
		free(temp);
	} else if (head -> nextNode != NULL) {
		while (current -> nextNode != NULL && strcmp(current -> nextNode -> songName, songToDelete) != 0) {
		    current = current -> nextNode;
		}
		if (current->nextNode != NULL) {
			if (strcmp(current -> nextNode -> songName, songToDelete) == 0) {
				temp = current -> nextNode;
				current -> nextNode = temp -> nextNode;
				free(temp -> songName);
    		    free(temp -> artist);
    		    free(temp -> genre);
    		    free(temp);
			} 
		}
	}
	return head;
}

//The following function empties the entire music library at the end of the program, and frees all allocated memory
void emptyLibrary(Node *head) {
	Node *current = head;
	while (current != NULL) {
		Node *songToDelete;
		songToDelete = current;
		songNameDeleted(current -> songName);
		free(songToDelete -> songName);
		free(songToDelete -> artist);
		free(songToDelete -> genre);
		free(songToDelete);
		current = current -> nextNode;
	}
}