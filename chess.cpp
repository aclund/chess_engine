#include <iostream>

using namespace std;

#include "functions.h"
#include "global.h"

int main(int argc, char *argv[]) {

	bool read_fen = false;
	bool random = false;
	bool run    = true;
	for( int i = 1; i < argc; i++ ) {
		if( strcmp(argv[i], "-fen") == 0 ) { read_fen = true; }
		if( strcmp(argv[i], "-r"  ) == 0 ) { run = false; random = true; }
		if( strcmp(argv[i], "-off") == 0 ) { run = false; }
	}
	if( read_fen ) { convert_fen(); }
	else{ 
		turn = 1;
	}

	ask_user();

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
		turn *= -1;
		//break;
	}

	return 0;
}
