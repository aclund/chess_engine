
using namespace std;

#include "global.h"

int score( int *board_in ) {

	int i_score = 0;

	for( int index = 0; index < 64; index++ ) {
		i_score += piece_score[board_in[index] + 6]; // Positive array indexing
	}

	return i_score;
}
