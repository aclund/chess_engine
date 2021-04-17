#include <iostream>

using namespace std;

#include "functions.h"
#include "global.h"

int main(int argc, char *argv[]) {

	bool read_fen = false;
	bool random = false;
	bool run    = true;
	for( int i = 1; i < argc; i++ ) {
		if( strcmp(argv[i], "--fen") == 0 ) { read_fen = true; }
		if( strcmp(argv[i], "-r"   ) == 0 ) { run = false; random = true; }
		if( strcmp(argv[i], " -off") == 0 ) { run = false; }
		if( strcmp(argv[i], "--off") == 0 ) { run = false; }
	}
	if( read_fen ) { convert_fen(); }
	else{ 
		turn = 1;
	}

	params = new int[n_params];

	if( run or random ) {
		ask_user(run);
	}

	set_moves();

	while( true ) {
		write_board();
		if( turn == user_turn ) {
			move();
		}
		else {
			if( random ) {
				random_player();
			}
			else if( run ) {
				engine();
			}
			else {
				move();
			}
		}
/*
	cout << " king " << king_counter << endl;
	cout << " queen " << queen_counter << endl;
	cout << " rook " << rook_counter << endl;
	cout << " bishop " << bishop_counter << endl;
	cout << " knight " << knight_counter << endl;
	cout << " pawn " << pawn_counter << endl;
*/

		params[0] *= -1;
		turn *= -1;

		if( game_over() ) { break; }
	}

	return 0;
}
