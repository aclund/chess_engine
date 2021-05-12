#include <iostream>

using namespace std;

#include "functions.h"
#include "global.h"

int main(int argc, char *argv[]) {

	int ierr;
	params = new int[n_params];

	bool read_fen = false;
	bool random = false;
	bool run    = true;
	for( int i = 1; i < argc; i++ ) {
		if( strcmp(argv[i], "--fen") == 0 ) { read_fen = true; }
		if( strcmp(argv[i], "-r"   ) == 0 ) { run = false; random = true; }
		if( strcmp(argv[i], " -off") == 0 ) { run = false; }
		if( strcmp(argv[i], "--off") == 0 ) { run = false; }
	}
	if( read_fen ) { ierr = convert_fen(); }
	else{ set_bitboards( ); }
	if( ierr != 0 ) { return 0; }

	if( run or random ) { ask_user(run); }

	set_moves();

	while( true ) {
		ierr = check_bits( bitboards );
		if( ierr != 0 ) { break; }
		convert2board();
		write_board(board,params);
		if( params[0] == user_turn ) {
			move();
		}
		else {
			if( random ) {
				random_player();
			}
			else if( run ) {
				engine();
				break;
			}
			else {
				move();
			}
		}

		if( game_over( bitboards ) ) { break; }

	}

	free( params );

	return 0;
}
