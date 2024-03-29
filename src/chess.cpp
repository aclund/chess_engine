// CHESS ENGINE
// ============
// Usage chess [-c/--color (w/b)] [-d/--depth #] [--fen] [-r/--random] [--off] [-b/--basic]

#include "functions.h"

// Random 64 bit generator
mt19937_64 rand_64::rng;

int main(int argc, char *argv[]) {

	// Initialize mpi
	setup_mpi( argc, argv );

	// Command line arguments
	command_args( argc, argv );

	int ierr = 0;
	float move_counter = 1;
	Chess_Board chess_board;

	// Use [--fen] string to initialize board from file position.fen
	if( read_fen ) { ierr = convert_fen( &chess_board ); }
	else{ initial_position( &chess_board ); }
	stop_on_error( ierr );

	// Global piece moves and values
	set_moves( );

	int rand_seed;
	if( l_root ) {
		// Set user color
		if( run or random_moves ) { ask_user( run ); }
		else { user_turn = 0; }

		// Same random seed
		rand_seed = time(0);
	}
#ifdef MPI_ON
	MPI_Bcast( &user_turn, 1, MPI_INT, i_root, MPI_COMM_WORLD );
	MPI_Bcast( &max_depth, 1, MPI_INT, i_root, MPI_COMM_WORLD );
	MPI_Bcast( &rand_seed, 1, MPI_INT, i_root, MPI_COMM_WORLD );
#endif

	// Seed random number generator
	rand_64::seed(rand_seed);

	// Hash table that stores every previous position hash
	Hash hash_history;
	hash_history.append( chess_board );

	// Main game loop
	while( !game_over( chess_board, hash_history ) ) {

		// Error catch
		ierr = check_bits( chess_board );
		stop_on_error( ierr );

		// Write board
		if( l_root ) { write_board( chess_board ); }

		// Execute move
		if( (chess_board.Parameters & 1) == user_turn ) {
			move( &chess_board );
		}
		else {
			if( random_moves ) { random_player( &chess_board ); }
			else if( run )     { engine( &chess_board, hash_history ); }
			else               { move( &chess_board ); }
		}

		// Write position to file
		if( l_root ) { last_known_board( chess_board ); }

		// Store current hash
		hash_history.append( chess_board );

		move_counter += 0.5;
	}

	// Write Game Over
	if( l_root ) { is_over( chess_board, hash_history, move_counter ); }

#ifdef MPI_ON
	MPI_Finalize( );
#endif
	return 0;
}
