#include <string>
//#include <iostream>
//using namespace std;

#include "global.h"
#include "functions.h"

void print_binary(uint64_t number)
{
	if( number >> 1 ) {
		print_binary(number >> 1);
	}
	putc((number & 1) ? '1' : '0', stdout);
}

bool in_range(int row, int col) {
	if( row < 8 and row >= 0 and col < 8 and col >= 0 ) { return true; }
	else{ return false; }
}
void index_square(string square, int *row, int *column) {

	string move_letter_square = "abcdefgh";

	// Find target square
	*row = (int)square[1] - 48 - 1;
	for( int i = 0; i < 8; i++ ) {
		if( square[0] == move_letter_square[i] ) {
			*column = i;
			break;
		}
	}
	return;
}
int rc2index(int row, int column) {
        return row*8 + column;
}
void index2rc(int index, int *row, int *column) {
	*row = int(index/8);
	*column = index - int(index/8)*8;
        return;
}
int pawn_rel_rank( int i, int i_turn ) {
	int rel_rank = (1-i_turn)*4.5 + (int(i/8) + 1)*i_turn;
	//cout << "i, rel_rank = " << i << " "<< rel_rank << "\n";
	return rel_rank; 
}
string index2square( int index ) {
	string square = " ";

	int rel_row, rel_col;
	index2rc( index, &rel_row, &rel_col );

	if(      rel_col == 7 ) square += "h";
	else if( rel_col == 6 ) square += "g";
	else if( rel_col == 5 ) square += "f";
	else if( rel_col == 4 ) square += "e";
	else if( rel_col == 3 ) square += "d";
	else if( rel_col == 2 ) square += "c";
	else if( rel_col == 1 ) square += "b";
	else if( rel_col == 0 ) square += "a";

	if(      rel_row == 0 ) square += "1 ";
	else if( rel_row == 1 ) square += "2 ";
	else if( rel_row == 2 ) square += "3 ";
	else if( rel_row == 3 ) square += "4 ";
	else if( rel_row == 4 ) square += "5 ";
	else if( rel_row == 5 ) square += "6 ";
	else if( rel_row == 6 ) square += "7 ";
	else if( rel_row == 7 ) square += "8 ";

	return square;
}
