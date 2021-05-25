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
int move_counter = 1;

int main(int argc, char *argv[]) {

	clock_t whole = clock( );

	bool read_fen = false;
	bool random = false;
	bool run    = true;
	for( int i = 1; i < argc; i++ ) {
		if( strcmp(argv[i], "--fen") == 0 ) { read_fen = true; }
		if( strcmp(argv[i], "-r"   ) == 0 ) { run = false; random = true; }
		if( strcmp(argv[i], " -off") == 0 ) { run = false; }
		if( strcmp(argv[i], "--off") == 0 ) { run = false; }
	}
	if( read_fen ) { ierr = convert_fen( ); }
	else{ set_bitboards( ); }
	if( ierr != 0 ) { return 0; }

	if( run or random ) { ask_user( run ); }
	else { user_turn = 1; }

	set_moves( );

	while( true ) {
		ierr = check_bits( bitboards );
		if( ierr != 0 ) { break; }
		convert2board( );
		write_board( board, params );
		if( params[0] == user_turn ) {
			move( );
		}
		else {
			if( random ) {
				random_player( );
			}
			else if( run ) {
				engine( );
				//break;
			}
			else {
				move( );
			}
		}

		move_counter += 0.5;
		if( game_over( bitboards ) ) { is_over( bitboards, move_counter ); break; }

	}

	delete[] params;

	cout << "\n TIME in CHESS: " << (clock( ) - whole) / (double) CLOCKS_PER_SEC << "\n\n";

	return 0;
}
