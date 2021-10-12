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

        Move_Tree *root = new Move_Tree;

        //Find Depth 0
        root->moves_arr = newMoves( bitboards.Parameters, max_moves );
        int n_possible_moves = 0;
        all_moves( bitboards, root->moves_arr, &n_possible_moves );
	root->n_moves = n_possible_moves;

	//cout << "# Possible Moves = " << n_possible_moves << "\n";
	if( n_possible_moves == 0 ) { return; }

	int ierr = check_bits( bitboards );
	if( ierr != 0 ) { return; }

	srand (time(NULL));
	int rando_board = rand() % n_possible_moves;

	bitboards = preform_move( bitboards, root->moves_arr[rando_board] );

	delete[] root->moves_arr;
	delete   root;

	return;
}
