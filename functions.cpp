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
