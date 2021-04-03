#include <string>
#include <iostream>

using namespace std;

#include "functions.h"
#include "global.h"

int piece_convert(char piece) {
	if(	   piece == 'p' ) {
		return pawn;
	} else if( piece == 'n' ) {
		return knight;
	} else if( piece == 'b'  ) {
		return bishop;
	} else if( piece == 'r' ) {
		return rook;
	} else if( piece == 'q' ) {
		return queen;
	} else if( piece == 'k' ) {
		return king;
	}
	return 0;
}

int valid_move(string move_AN, int ierr) {

	ierr = 0;

	string string_move_piece  = "rnbqkp";
	string move_letter_square = "abcdefgh";
	string move_number_square = "12345678";

	// Check move string in range
	string move_square;
	int numbers = 0;
	int letters = 0;
	char read;
	bool found_piece = false;
	for( int n_read = 0; n_read < move_AN.length(); n_read++ ) {
		read = move_AN[n_read];
		if(  string_move_piece.find(read) != string::npos &&
			move_AN.length() != 2 && !found_piece ) {
			move_piece = turn*piece_convert(read);
			found_piece = true;
		}
		else if( move_letter_square.find(read) != string::npos ) {
			move_square[0] = read;
			letters++;
		}
		else if( move_number_square.find(read) != string::npos ) {
			move_square[1] = read;
			numbers++;
		}
	}
	if( !found_piece ) { move_piece = turn*pawn; }
	if( numbers != 1 ) { cout << "ONE row number only!!!\n"; return 1; }
	if( letters  < 1 ) { cout << "NO square letter?\n"; return 1; }
	// b is a duplicate and not handled
	else if( letters  > 1 ) {
		for( int n_read = 0; n_read < move_AN.length(); n_read++ ) {
                	read = move_AN[n_read];
                	if( move_letter_square.find(read) != string::npos ) {
                        	// Specify move_piece
			}
		}
	}

	// Find and check target square
	index_square(move_square, &move_row, &move_column); 
	move_index = rc2index(move_row, move_column);
	cout<< move_piece << "   " << move_row << " : " << move_column << " move_index = " << move_index <<endl;

	if( board[move_row][move_column]*turn > 0 ) { // Your piece on square
		cout << "Occupado\n";
		return 1;
	}

	// Load board into temporary for some reason then find every possible move
	int max_tree = 111;
	int **possible_boards = new int*[max_tree];
	for( int i = 0; i < max_tree; i++ ) {
		possible_boards[i] = new int[64]; 
	}

	int count = 0;
	for( int row = 0; row < 8; row++ ) {
		for( int col = 0; col < 8; col++ ) {
			possible_boards[0][count] = board[row][col];
			count++;
		}
	}
	n_possible_moves = 0;
	all_moves(possible_boards[0], params, &possible_boards[1], turn);
	cout << "# Possible Moves = " << n_possible_moves << "\n";

	int index = 0;
	for( int n_boards = 1; n_boards < n_possible_moves + 1; n_boards++ ) {
		//cout << "possible spot =" << possible_boards[move_index][n_boards] << "\n";
		if( move_piece == possible_boards[n_boards][move_index] ) {
		// && right piece??
			for( int row = 0; row < 8; row++ ) {
				for( int col = 0; col < 8; col++ ) {
					board[row][col] = possible_boards[n_boards][index];
					index++;
				}
			}
			index = 0;
			//write_board();

			// Delete tree
			for( int i = 0; i < max_tree; i++ ) {
				delete [] possible_boards[i];
			}
			delete [] possible_boards;

			return 0;
		}
	}

	// Move not found
	return 1;
}
