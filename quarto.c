#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.c"

//code by Cyprien DE LA POËZE D'HARAMBURE and Hugo MARTIN


void print_void(){
/**
 * @brief Prints multiple spaces as wide as a board's cell width.
 * */
	printf("     ");
}


void print_line(){
/**
 * @brief Prints a board horizontal line.
 * */
		printf("   _________________________\n");
}
	

void print_type_piece(piece p){
/**
 * @brief Prints a symbol representing a piece from a piece object.
 * @param piece A piece object
 * */

	switch (piece_color(p)){
		case BLUE :											                                            // If the piece is BLUE (white),
			switch (piece_shape(p)){					                                        // Get the shape of the piece, then print it
				case SQUARE :
					printf("  □  ");
					break;
				case CIRCULAR :
					printf("  ○  ");
					break;
			}
			break;
		case RED:												                                            // If the piece is RED (black),
			switch (piece_shape(p)){					                                        // Get the shape of the piece, then print it
				case SQUARE:
					printf("  ■  ");
					break;
				case CIRCULAR :
          printf("  ●  ");
					break;
			}
			break;
	}
}


void print_top_piece(piece p){
/**
 * @brief Prints the top type of a piece, SOLID or HOLLOW.
 * @param piece A piece object.
 * */
	switch(piece_top(p)){
		case HOLLOW:
			printf("  •  ");
			break;
		case SOLID:
			print_void();
			break;
	}
}


void print_tall_piece(piece p){
/**
 * @brief Prints the upper part of a piece.
 * @param piece A piece object.
 * */
	if(piece_size(p) == TALL){
		print_type_piece(p);
	}
	else{
		print_void();
	}
}


void print_bottom_piece(piece p){
/**
 * @brief Prints the bottom of a piece.
 * @param piece A piece object.
 * */
		print_type_piece(p);
}


void list_left_pieces(board game, piece left[16], int* number){
/**
 * @brief Function that returns a list of all the unplaced pieces, and the number of those.
 * @param game A board generated by board.h.
 * @param left[16] An Array to store the pieces.
 * @param *number An int address to return the amount of unplaced pieces.
 * */
	int index = 0;
	*number = 0;
	for(int color = 0; color < 2; color++){																	//4 loops to get all the possibilities
		for(int size = 0; size < 2; size++){
			for(int shape = 0; shape < 2; shape++){
				for(int top = 0; top < 2; top++){
					piece p = get_piece_from_characteristics(size, shape, color, top);
					if(!is_present_on_board(game, p)){
						left[index] = p;
						*number += 1;
					}
					else{
						left[index] = NULL;
					}
					index++;
				}
			}
		}
	}
}


void display_left_pieces(board game, int* number){
/**
 * @brief Displays the pieces left to place.
 * @param game A board generated by board.h.
 * */
	piece left[17] = {};
	list_left_pieces(game, left, number);
	printf("\nPIeces left : \n");
//_________________________________________________________________________________________________________

	for(int j = 0; j < 16; j++){																					           // Displays the Hollow dot "•"
		if(left[j] != NULL){						   																			   // ift he piece top is HOLLOW
			print_top_piece(left[j]);
		}
		else{
			print_void();
		}
	}
	printf("\n");

//_________________________________________________________________________________________________________

	for(int j = 0; j < 16; j++){																			           		// Displays the top part of the piece
		if(left[j] != NULL){
			print_tall_piece(left[j]);
		}
		else{
			print_void();
		}
	}
	printf("\n");

//_________________________________________________________________________________________________________

	for(int j = 0; j < 16; j++){
		if(left[j] != NULL){																				  		        	// Displays the botoom part of the piece
			print_bottom_piece(left[j]);
		}
		else{
			print_void();
		}
	}
	printf("\n");

//_________________________________________________________________________________________________________

	for(int j = 0; j < 16; j++){																				          	// Displays the number at the bottom of the pieces
		printf("  %02d ", j+1);
	}
	printf("\n");
}


void print_row(board game, int row){
/**
 * @brief Displays an entire board row in the terminal.
 * @param game A board generated by board.h.
 * @param row A row number between 0 and DIMENSION-1.
 * */

	piece row_pieces[4] = {get_piece(game, row,0), get_piece(game, row,1), get_piece(game, row,2), get_piece(game, row,3)};
	print_line();

//_________________________________________________________________________________________________________
	printf("   ");
	for(int j = 0; j < 4; j++){																					           // Displays the Hollow dot "•"
		printf("|");																										           // ift he piece top is HOLLOW
		if(is_occupied(game, row, j)){
			print_top_piece(row_pieces[j]);
		}
		else{
			print_void();
		}
	}
	printf("|\n");
	
//_________________________________________________________________________________________________________
	printf(" %d ", row+1);
	for(int j = 0; j < 4; j++){																			           		// Displays the top part of the piece
		printf("|");																										        // if the piece is TALL
		if(is_occupied(game, row, j)){
			print_tall_piece(row_pieces[j]);
		}
		else{
			print_void();
		}
	}
	printf("|\n");
	
//_________________________________________________________________________________________________________
	printf("   ");
	for(int j = 0; j < 4; j++){																				          	// Displays the botoom part of the piece
		printf("|");
		if(is_occupied(game, row, j)){
			print_bottom_piece(row_pieces[j]);
		}
		else{
			print_void();
		}
	}
	printf("|\n");
}


void display_board(board game,int *number){
/**
 * @brief Clears the terminal and displays the entire board in the terminal.
 * @param game A 4*4 board to display.
 * */
	printf("\033[2J");
	printf("      1     2     3     4   \n");								 //Prints the columns numbers
	for(int i = 0; i < 4	; i++){
		print_row(game, i);
	}
	 print_line();   														      // Prints bottom line
	 display_left_pieces(game, number);
}


piece choice(board game,int num_piece){
/**
 * @brief Takes an int between 1 and 16 as parameters ans returns the corresponding piece.
 * @param game A game object.
 * @param num_piece An int between 1 and 16 included.
 * */
	piece chosen_piece;
	switch (num_piece){
		case 1 :
			chosen_piece = get_piece_from_characteristics(0,0,0,0);
			break;
		case 2 :
			chosen_piece = get_piece_from_characteristics(0,0,0,1);
			break;
		case 3 :
			chosen_piece = get_piece_from_characteristics(0,1,0,0);
			break;
		case 4 :
			chosen_piece = get_piece_from_characteristics(0,1,0,1);
			break;
		case 5 :
			chosen_piece = get_piece_from_characteristics(1,0,0,0);
			break;
		case 6 :
			chosen_piece = get_piece_from_characteristics(1,0,0,1);
			break;
		case 7 :
			chosen_piece = get_piece_from_characteristics(1,1,0,0);
			break;
		case 8 :
			chosen_piece = get_piece_from_characteristics(1,1,0,1);
			break;
		case 9 :
			chosen_piece = get_piece_from_characteristics(0,0,1,0);
			break;
		case 10 :
			chosen_piece = get_piece_from_characteristics(0,0,1,1);
			break;
		case 11 :
			chosen_piece = get_piece_from_characteristics(0,1,1,0);
			break;
		case 12 :
			chosen_piece = get_piece_from_characteristics(0,1,1,1);
			break;
		case 13 :
			chosen_piece = get_piece_from_characteristics(1,0,1,0);
			break;
		case 14 :
			chosen_piece = get_piece_from_characteristics(1,0,1,1);
			break;
		case 15 :
			chosen_piece = get_piece_from_characteristics(1,1,1,0);
			break;
		case 16 :
			chosen_piece = get_piece_from_characteristics(1,1,1,1);
			break;
		
	}
	return chosen_piece;
}


int turn(board game, int turns, char nicks[2][30]){
/**
 * @brief Starts and ends a player's turn.
 * @param game A game object.
 * */
	int chosen_line,chosen_column,num_piece;
	piece chosen_piece;
	//_________________________________________________________________________________________________________________________________________
	printf("\n%s, what piece do you want to give %s? (Give its number)\n", nicks[(turns+1)%2], nicks[turns%2]);			//Other player gives piece to place
	scanf("%d",&num_piece);
	while(num_piece < 1 || num_piece > 16){																										//Asks for the piece number
		printf("This number is not valid, please input another one.\n");
		while(scanf("%d", &num_piece) == 0) {
			getchar();
		}
	}
	//___________________________________________________________________________________________________________________________________________
	printf("\n%s, what line do you want to place it?\n", nicks[turns%2]);
	scanf("%d",&chosen_line);																																	//Asks for the line the piece will be placed
	while(chosen_line > 4 || chosen_line < 1){
		printf("This number is not valid, please input another one.\n");
		while(scanf("%d", &chosen_line) == 0) {
			getchar();
		}
	}
	//____________________________________________________________________________________________________________________________________________
	printf("\n%s, what column do you want to place it?\n", nicks[turns%2]);
	scanf("%d",&chosen_column);																															//Asks for the column the piece will be placed
	while(chosen_column > 4 || chosen_column < 1){ 
		printf("This number is not valid, please input another one.\n");
		while(scanf("%d", &chosen_column) == 0) {
			getchar();
		}
	}
	//_____________________________________________________________________________________________________________________________________________
	chosen_piece = choice(game,num_piece);																										 //Get the piece from the number the user input
	if(!(is_occupied(game, chosen_line-1, chosen_column-1)) && !(is_present_on_board(game, chosen_piece))){
		place_piece(game, chosen_line-1, chosen_column-1, chosen_piece);															 //Places the piece
		return 1;
	}
	else{
		return 0;
	}
}


int are_identical(char nick1[30], char nick2[30]){
/**
 * @brief Checks if two strings are identical, returns boolean.
 * @param nick1 A string
 * @param nick2 A string
 * */
	int index = 0;
	while(nick1[index] != '\0'){
		if(nick1[index] != nick2[index]){
			return 0;
		}
		index++;
	}
	if(nick2[index] == '\0'){
		return 1;
	}
	return 0;
}
		

void ask_names(char nicks[2][30]){
/**
 * @brief Asks the players for their nicknames and prevents dupes.
 * @param nicks An empty array tostore the names.
 * */
	for(int i = 0; i < 2; i++){
		printf("Player %d,  please input your nickname.\n", i+1);
		scanf("%s", nicks[i]);
		printf("\n");
	}

	while(are_identical(nicks[0], nicks[1])){																			//prevents both players to get the same nickname
		printf("You cannot chose the same nickname as player 1.\n");
		while(scanf("%s", nicks[0]) ==0 && are_identical(nicks[0], nicks[1])){		
			getchar();
		}
	}
}


void play_game(board game){
/**
 * @brief Plays the actual game.
 * @param game A 4*4 board object.
 * */
	printf("\033[2J");
	int turns = rand()%2-1;															//turns gets -1 because we increment the value before the actual turn, so we can start the first turn with turns = 0 or turns = 1
	int number = 1;																		//So the first person to play is random
	char nicks[2][30];
	ask_names(nicks);
	int check =1;
	
	while(has_winner(game) == 0 && number != 0){									//while no winner, or still pieces left, the game itself
		
		display_board(game, &number);
		if(check == 1){
			turns++;
			
		}
		else{
			printf("\nThe piece could not be placed, try another one or another location!");
		}
		check = turn(game, turns, nicks);
	}
	
	display_board(game, &number);
	
	if(has_winner(game)){																				//if someone won
		printf("%s, you won!\n", nicks[turns%2]);
	}
	
	else{																											//else, the game ended on a tie
		printf("That's a tie, no more pieces left.\n");
	}
}
