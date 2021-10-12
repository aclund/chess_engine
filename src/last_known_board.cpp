#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include "global.h"
#include "functions.h"

char piece_convert(int);

void last_known_board( ) {

	ofstream fenfile;
	fenfile.open( "last_known_position.fen", ofstream::out | ofstream::trunc );

	int row = 7, col = 0, emptys;
	while( row >= 0 ) {
		if( board[rc2index(row,col)] != 0 ) {
			fenfile << piece_convert(board[rc2index(row,col)]);
			col++;
		}
		else {
			emptys = 0;
			while( board[rc2index(row,col)] == 0 ) {
				emptys++;
				col++;
				if( col == 8 ) {
					fenfile << emptys;
					fenfile << "/";
					emptys = 0;
					row --; col = 0;
				}
			}
			if( emptys != 0 ) { fenfile << emptys; }
		}

		if( col == 8 ) {
			row--; col = 0;
			if( row >= 0 ) { fenfile << "/";}
		}

	}

	if( bitboards.Parameters & 1 ) fenfile << " b ";
	else fenfile << " w ";

	uint64_t temp;

	// Castle Rights
	temp = bitboards.Parameters;
	temp %= 32;
	BIT_CLEAR( temp, 0 );
	if( !temp ) fenfile << "-";
	if( (temp >> 1) & 1 ) fenfile << "K";
	if( (temp >> 2) & 1 ) fenfile << "Q";
	if( (temp >> 3) & 1 ) fenfile << "k";
	if( (temp >> 4) & 1 ) fenfile << "q";

	// En Passant
	temp = bitboards.Parameters;
	BIT_CLEAR( temp, 0 ); BIT_CLEAR( temp, 1 ); BIT_CLEAR( temp, 2 ); BIT_CLEAR( temp, 3 ); BIT_CLEAR( temp, 4 );
	BIT_CLEAR( temp, 5 ); BIT_CLEAR( temp, 6 ); BIT_CLEAR( temp, 7 ); BIT_CLEAR( temp, 8 ); BIT_CLEAR( temp, 9 );
	BIT_CLEAR( temp, 10); BIT_CLEAR( temp, 11);
	temp /= 4096;
	if( temp != 0 ) {
		fenfile << index2square( temp );
	}
	else {
		fenfile << " - ";
	}

	// Halfmove Clock
	temp = bitboards.Parameters;
	temp %= 4096;
        BIT_CLEAR( temp, 0 ); BIT_CLEAR( temp, 1 ); BIT_CLEAR( temp, 2 ); BIT_CLEAR( temp, 3 ); BIT_CLEAR( temp, 4 );
	temp /= 32;
	fenfile << temp;

	fenfile << "\n";

	fenfile.close();
	return;
}

char piece_convert( int piece ) {
	switch( piece ) {
	  case -6:
		return 'k';
	  break;
	  case -5:
		return 'q';
	  break;
	  case -4:
		return 'r';
	  break;
	  case -3:
		return 'b';
	  break;
	  case -2:
		return 'n';
	  break;
	  case -1:
		return 'p';
	  break;
	  case  6:
		return 'K';
	  break;
	  case  5:
		return 'Q';
	  break;
	  case  4:
		return 'R';
	  break;
	  case  3:
		return 'B';
	  break;
	  case  2:
		return 'N';
	  break;
	  case  1:
		return 'P';
	  break;

	  default:
		return ' ';
		cout << " ERROR last_known_board!\n";
	  break;
	}
}
