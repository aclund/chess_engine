#include <iostream>

using namespace std;

#include "functions.h"
#include "global.h"
#include "initialize.h"
#include "convert_binary.h"
#include "piece_moves.h"
#include "check_check.h"

void is_over(Chess_Board);

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

		if( game_over(bitboards) ) { is_over(bitboards); break; }

	}

	free( params );

	return 0;
}

void is_over( Chess_Board chess_board ) {
        int i_turn;
	Pieces *your_pieces, *their_pieces;
        switch( chess_board.Parameters & 1 ) {
          case 0: // White to Move
                your_pieces  = &chess_board.White;
                their_pieces = &chess_board.Black;
                i_turn = 1;
          break;
          case 1: // Black to Move
                your_pieces  = &chess_board.Black;
                their_pieces = &chess_board.White;
                i_turn = -1;
          break;
	}

	convert2board();
	write_board(board,params);

	int n_checks = 0;
	Moves_temp *check_pieces = newTemp(2);
	check_check( your_pieces->King, your_pieces->All, their_pieces, 
		     ~chess_board.All_Pieces, i_turn, check_pieces, &n_checks );

	if( n_checks == 0 ) {
		cout << " STALEMATE! \n";
	}
	else {
		cout << " CHECKMATE! \n";
	}
}
