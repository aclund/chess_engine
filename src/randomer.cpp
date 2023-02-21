#include "functions.h"

mt19937_64 rand_64::rng;

int main(int argc, char *argv[]) {

	// Command line arguments
	command_args( argc, argv );

	int ierr = 0;
	float move_counter = 1;
	Chess_Board chess_board;

	// Use [--fen] string to initialize board from file position.fen
	if( read_fen ) {
		ierr = convert_fen( &chess_board );
		if( ierr != 0 ) { return 0; }
	}
	else{ initial_position( &chess_board ); }

	// Set user color
	user_turn = 1;

	// Global piece moves and values
	set_moves( );

	// Seed random number generator
	rand_64::seed(time(0));

	// Hash table that stores every previous position hash
	Hash hash_history;
	hash_history.append( chess_board );

	// Main game loop
	while( !game_over( chess_board, hash_history ) ) {

		// Error catch
		ierr = check_bits( chess_board ); if( ierr != 0 ) { return 0; }

		// Write board
		//write_board( chess_board );

		// Execute move
		random_player( &chess_board );

		// Write position to file
		//last_known_board( chess_board );

		// Store current hash
		hash_history.append( chess_board );

		move_counter += 0.5;
	}

	// Write Game Over
	is_over( chess_board, hash_history, move_counter );

	return 0;
}
