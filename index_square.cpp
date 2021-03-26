#include <string>

using namespace std;

#include "functions.h"
#include "global.h"

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
