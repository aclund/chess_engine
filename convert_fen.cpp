#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>

using namespace std;

#include "functions.h"
#include "global.h"

//void convert_FEN(string FEN, int board_out[8][8]) {
void convert_fen() {

	string FEN;

	int board_in[8][8];

	ifstream fenfile;
	fenfile.open("position.fen");
	fenfile.seekg(0, ios::end);   
	FEN.reserve(fenfile.tellg());
	fenfile.seekg(0, ios::beg);

	FEN.assign((istreambuf_iterator<char>(fenfile)),
        	    istreambuf_iterator<char>());

	for( int row = 0; row < 8; row++ ) {
		for( int column = 0; column < 8; column++ ) {
			board_in[row][column] = 0;
		}
	}

	int i = 0;
	int row = 0;
	int column = 0;
	char ifen = FEN[i];
	while( ifen != ' ' ) {
		if( ifen == '/' ) { row++; column = 0; }
		else if( string("12345678").find(ifen) != string::npos ) { column += (int)ifen-48; }
		else if( ifen == 'P' ) { board_in[row][column] = w_pawn; column++; }
		else if( ifen == 'N' ) { board_in[row][column] = w_knight; column++; }
		else if( ifen == 'B' ) { board_in[row][column] = w_bishop; column++; }
		else if( ifen == 'R' ) { board_in[row][column] = w_rook; column++; }
		else if( ifen == 'Q' ) { board_in[row][column] = w_queen; column++; }
		else if( ifen == 'K' ) { board_in[row][column] = w_king; column++; }
		else if( ifen == 'p' ) { board_in[row][column] = b_pawn; column++; }
		else if( ifen == 'n' ) { board_in[row][column] = b_knight; column++; }
		else if( ifen == 'b' ) { board_in[row][column] = b_bishop; column++; }
		else if( ifen == 'r' ) { board_in[row][column] = b_rook; column++; }
		else if( ifen == 'q' ) { board_in[row][column] = b_queen; column++; }
		else if( ifen == 'k' ) { board_in[row][column] = b_king; column++; }
		i++;
		ifen = FEN[i];
	}

	int end = i;
	ifen = FEN[i+1];
	if( ifen == 'w' ) { turn =  1; }
	if( ifen == 'b' ) { turn = -1; }
	end += 2;

	for( int row = 0; row < 8; row++ ) {
		for( int column = 0; column < 8; column++ ) {
			board[7-row][column] = board_in[row][column];
			//cout << board_in[row][column] << "  ";
		}
		//cout << "\n";
	}

	return;
}
