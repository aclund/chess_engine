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
