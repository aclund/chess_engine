#include "functions.h"
#include "colormod.h"

void squares( int board_in[64], int row ) {
	Color::Modifier black(Color::FG_BLACK);
	Color::Modifier white(Color::FG_WHITE);
	//Color::Modifier white(Color::FG_RED);
	//Color::Modifier back_black(Color::BG_BLACK);
	//Color::Modifier back_white(Color::BG_WHITE);
	Color::Modifier back_black(Color::BG_BLACK);
	Color::Modifier back_white(Color::BG_WHITE);
	Color::Modifier def(Color::FG_DEFAULT);
	Color::Modifier back_def(Color::BG_DEFAULT);

	string piece;
	int col = row%2;

	cout << back_def << " |";
	if( col%2 == 0 ) {
		for( int c = 0; c < 4; c ++ ) {
			cout << back_black << "        ";
			cout << back_white << "        ";
		}
	}
	else {
		for( int c = 0; c < 4; c ++ ) {
			cout << back_white << "        ";
			cout << back_black << "        ";
		}
	}
	cout << back_def << "\n";
	cout << row+1 << "|";


        for( int i = 0; i < 8; i++ ) {

		if( abs(board_in[row*8+i]) == pawn   ) { piece = "\u2659"; }
		if( abs(board_in[row*8+i]) == knight ) { piece = "\u2658"; }
		if( abs(board_in[row*8+i]) == bishop ) { piece = "\u2657"; }
		if( abs(board_in[row*8+i]) == rook   ) { piece = "\u2656"; }
		if( abs(board_in[row*8+i]) == queen  ) { piece = "\u2645"; }
		if( abs(board_in[row*8+i]) == king   ) { piece = "\u2654"; }

		if( col%2 == 0 ) {
			cout << back_black;
		}
		else {
			cout << back_white;
		}

		if( board_in[row*8+i] == 0 ) {
			cout << "        ";
		} else if( board_in[row*8+i] > 0 ) {
			cout << "   " << white << piece << def << "    ";
		} else if( board_in[row*8+i] < 0 ) {
			cout << "   " << black << piece << def <<"    ";
		}

		cout << back_def;
		col++;
	}

	cout << back_def << def << "\n |";
	if( col%2 == 0 ) {
		for( int c = 0; c < 4; c ++ ) {
			cout << back_black << "        ";
			cout << back_white << "        ";
		}
	}
	else {
		for( int c = 0; c < 4; c ++ ) {
			cout << back_white << "        ";
			cout << back_black << "        ";
		}
	}
	cout << back_def << "\n";

	cout << back_def << def;
	
	return;
}

void write_board( Chess_Board bitboards ) {

	int board[64], params[6];
	convert2board( bitboards, board, params );

	cout << "\e[1m";
	cout << "\n";
	cout << "     A       B       C       D       E       F       G       H\n";
	cout << "  ________________________________________________________________\n";

	int row;
        for( int i = 0; i < 8; i++ ) {
		if(      user_turn == 1 ) { row = i + 1; }
		else if( user_turn == 0 ) { row = 8 - i; }
		else{ cout << " ERROR in write_board_in\n"; }

                squares(board, row-1);
	}

	if(      params[0] ==  1 ) { cout << "  WHITE to move - "; }
	else if( params[0] == -1 ) { cout << "  BLACK to move - "; }
	else { cout << " ERROR: i_turn in write "; }

#ifdef DEBUG
	if( params[1] == 1 ) { cout << "K"; }
	if( params[2] == 1 ) { cout << "Q"; }
	if( params[3] == 1 ) { cout << "k"; }
	if( params[4] == 1 ) { cout << "q"; }
	cout << "  " << params[5] << "\n";
#endif

	cout << "\n\e[0m\n\n";

	return;
}
