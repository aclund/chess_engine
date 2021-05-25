#include <iostream>
#include <cstring>
#include <time.h>

using namespace std;

#include "functions.h"
#include "global.h"
#include "initialize.h"
#include "convert_binary.h"
#include "piece_moves.h"
#include "check_check.h"

int ierr;
int n_params = 6;
int  *params = new int[n_params];

int main(int argc, char *argv[]) {

	clock_t whole = clock( );

	bool read_fen = false;
	for( int i = 1; i < argc; i++ ) {
		if( strcmp(argv[i], "--fen") == 0 ) { read_fen = true; }
	}
	if( read_fen ) { ierr = convert_fen( ); }
	else{ set_bitboards( ); }
	if( ierr != 0 ) { return 0; }

	set_moves( ); user_turn = 1;

	float turn_counter = 1;
	while( true ) {
		random_player( );

		turn_counter += 0.5;
		if( game_over( bitboards ) ) { is_over( bitboards, turn_counter ); break; }
	}

	delete[] params;

	cout << "\n TIME in CHESS: " << (clock( ) - whole) / (double) CLOCKS_PER_SEC << "\n\n";

	return 0;
}
