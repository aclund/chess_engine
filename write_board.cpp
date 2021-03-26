#include <iostream>
#include <string>

using namespace std;

#include "functions.h"
#include "global.h"
#include "colormod.h"

void squares( int row ) {
	Color::Modifier black(Color::FG_BLACK);
	Color::Modifier white(Color::FG_WHITE);
	Color::Modifier def(Color::FG_DEFAULT);

	string piece;
        for( int i = 0; i < 8; i++ ) {

		if( abs(board[row][i]) == pawn   ) { piece = "p"; }
		if( abs(board[row][i]) == knight ) { piece = "n"; }
		if( abs(board[row][i]) == bishop ) { piece = "b"; }
		if( abs(board[row][i]) == rook   ) { piece = "r"; }
		if( abs(board[row][i]) == queen  ) { piece = "q"; }
		if( abs(board[row][i]) == king   ) { piece = "k"; }

		if( board[row][i] == 0 ) {
			cout << "    ";
		} else if( board[row][i] > 0 ) {
			cout << " " << white << piece << def << "  ";
		} else if( board[row][i] < 0 ) {
			cout << " " << black << piece << def <<"  ";
		}
	}
	
	return;
}

void write_board( ) {

	cout << "\n";
	cout << "   A   B   C   D   E   F   G   H\n";
	cout << " _______________________________\n";

	int row;
        for( int i = 0; i < 8; i++ ) {
		row = 8 - i;
		cout << row << "|";
                squares(row-1);
		if( i != 7 ) {
			cout << "\n" << " |\n";
		} else {
			cout << "\n\n";
		}
	}
	return;
}
