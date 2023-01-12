#include <fstream>
#include "functions.h"

int convert_fen( Chess_Board *bitboards ) {

	int ierr = 0, fen_length = 100;
	char FEN[fen_length];

	if( l_root ) {
		ifstream fenfile;
		fenfile.open("position.fen");
		if( fenfile.fail() ) {
			cout << " Could NOT find file 'position.fen'!\n";
			ierr = 1;
		}
		fenfile.getline( FEN, fen_length );
	}
	MPI_Bcast( &FEN, fen_length, MPI_CHAR, i_root, MPI_COMM_WORLD );

	int board[64];
	for( int i=0; i<64; i++ ) {
		board[i] = 0;
	}

	int i = 0;
	int row = 0;
	int column = 0;
	char ifen = FEN[i];
	while( ifen != ' ' ) {
		if( ifen == '/' ) { row++; column = 0; }
		else if( string("12345678").find(ifen) != string::npos ) { column += (int)ifen-48; }
		else if( ifen == 'P' ) { board[(7-row)*8+column] = w_pawn;   column++; }
		else if( ifen == 'N' ) { board[(7-row)*8+column] = w_knight; column++; }
		else if( ifen == 'B' ) { board[(7-row)*8+column] = w_bishop; column++; }
		else if( ifen == 'R' ) { board[(7-row)*8+column] = w_rook;   column++; }
		else if( ifen == 'Q' ) { board[(7-row)*8+column] = w_queen;  column++; }
		else if( ifen == 'K' ) { board[(7-row)*8+column] = w_king;   column++; }
		else if( ifen == 'p' ) { board[(7-row)*8+column] = b_pawn;   column++; }
		else if( ifen == 'n' ) { board[(7-row)*8+column] = b_knight; column++; }
		else if( ifen == 'b' ) { board[(7-row)*8+column] = b_bishop; column++; }
		else if( ifen == 'r' ) { board[(7-row)*8+column] = b_rook;   column++; }
		else if( ifen == 'q' ) { board[(7-row)*8+column] = b_queen;  column++; }
		else if( ifen == 'k' ) { board[(7-row)*8+column] = b_king;   column++; }
		i++;
		ifen = FEN[i];
	}
	int end = i;

	int params[6];
	for( int i = 0; i < 6; i++ ) {
		params[i] = 0;
	}

	ifen = FEN[end+1];
	if( ifen == 'w' ) { params[0] =  1; }
	if( ifen == 'b' ) { params[0] = -1; }
	end += 2;

	ifen = FEN[end+1];
	if( ifen == '-' ) { end += 2; }
	else {
		while( ifen != ' ' ) {
			if(      ifen == 'K' ) { params[1] = 1; }
			else if( ifen == 'Q' ) { params[2] = 1; }
			else if( ifen == 'k' ) { params[3] = 1; }
			else if( ifen == 'q' ) { params[4] = 1; }
			end += 1;
			ifen = FEN[end+1];
		}
		end += 1;
	}

	ifen = FEN[end+1];
	if( ifen == '-' ) { params[5] = -1; }
	else { 
		int pawn_row, pawn_col;
		index_square( string(1,FEN[end+1]) + FEN[end+2], &pawn_row, &pawn_col );
		params[5] = rc2index( pawn_row, pawn_col );
		//cout<< pawn_row << " " << pawn_col << " " << params[5] << endl;
	}

	convert2bits( board, params, bitboards );

	return ierr;
}
