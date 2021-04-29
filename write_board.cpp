#include <iostream>
#include <string>

using namespace std;

#include "functions.h"
#include "global.h"
#include "colormod.h"

void squares( int row ) {
	Color::Modifier black(Color::FG_BLACK);
	Color::Modifier white(Color::FG_WHITE);
	Color::Modifier back_black(Color::BG_BLACK);
	Color::Modifier back_white(Color::BG_WHITE);
	Color::Modifier def(Color::FG_DEFAULT);
	Color::Modifier back_def(Color::BG_DEFAULT);

	string piece;
	int col = row%2;
        for( int i = 0; i < 8; i++ ) {

		if( abs(board[row][i]) == pawn   ) { piece = "\u2659"; }
		if( abs(board[row][i]) == knight ) { piece = "\u2658"; }
		if( abs(board[row][i]) == bishop ) { piece = "\u2657"; }
		if( abs(board[row][i]) == rook   ) { piece = "\u2656"; }
		if( abs(board[row][i]) == queen  ) { piece = "\u2645"; }
		if( abs(board[row][i]) == king   ) { piece = "\u2654"; }

		if( col%2 == 0 ) {
			cout << back_black;
		}
		else {
			cout << back_white;
		}

		if( board[row][i] == 0 ) {
			cout << "    ";
		} else if( board[row][i] > 0 ) {
			cout << " " << white << piece << def << "  ";
		} else if( board[row][i] < 0 ) {
			cout << " " << black << piece << def <<"  ";
		}

		cout << back_def;
		col++;
	}

	cout << back_def << def;
	
	return;
}

void write_board( ) {

	cout << "\n";
	cout << "   A   B   C   D   E   F   G   H\n";
	cout << " _______________________________\n";

	int row;
        for( int i = 0; i < 8; i++ ) {
/*
		if(      user_turn == -1 ) { row = i + 1; }
		else if( user_turn ==  1 ) { row = 8 - i; }
		else{ cout << " ERROR in write_board\n"; }
*/
row = 8 - i;
		cout << row << "|";
                squares(row-1);
		if( i != 7 ) {
			cout << "\n" << " |\n";
		} else {
			cout << "\n\n";
		}
	}

	if(      params[0] ==  1 ) { cout << " WHITE to move: "; }
	else if( params[0] == -1 ) { cout << " BLACK to move: "; }
	else { cout << " ERROR: i_turn in write "; }

	if( params[1] == 1 ) { cout << "K"; }
	if( params[2] == 1 ) { cout << "Q"; }
	if( params[3] == 1 ) { cout << "k"; }
	if( params[4] == 1 ) { cout << "q"; }

	cout << "  " << params[5] << "\n";

	return;
}
