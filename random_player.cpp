#include <string>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

#include "functions.h"
#include "global.h"
#include "initialize.h"
#include "convert_binary.h"
#include "preform_move.h"

void random_player() {

        //Move_Tree *root = nullptr;
        Move_Tree *root;

        //Find Depth 0
        Moves *moves_add = newMoves( bitboards.Parameters, max_moves );
        int n_possible_moves = 0;
        all_moves( bitboards, moves_add, &n_possible_moves );

        root = newTree( moves_add, n_possible_moves );
	cout << "# Possible Moves = " << n_possible_moves << "\n";
	if( n_possible_moves == 0 ) { return; }

	int ierr = check_bits( bitboards );
	if( ierr != 0 ) { return; }

	//srand (time(NULL));
	int rando_board = rand() % n_possible_moves;

	bitboards = preform_move( bitboards, moves_add[rando_board] );

	return;
}
