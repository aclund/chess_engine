#include <iostream>

using namespace std;

#include "global.h"

bool in_range(int row, int col) {
	if( row < 8 and row >= 0 and col < 8 and col >= 0 ) { return true; }
	else{ return false; }
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
void write_from2d( int **possible_boards ) {
	cout << "\n";
	int index = 0;
	for( int row = 0; row < 8; row++ ) {
		for( int col = 0; col < 8; col++ ) {
			if( possible_boards[0][index] < 0 ) {
				cout << possible_boards[0][index] << " ";
			}
			else {
				cout << " " << possible_boards[0][index] << " ";
			}
			index++;
		}
		cout << "\n";
	}
        return;
}
