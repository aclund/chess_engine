#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#include "functions.h"
#include "global.h"
#include "initialize.h"

void engine( ) {

	//Move_Tree *root = nullptr;
	Move_Tree *root;

	//Find Depth 0
	Moves *moves_add = newMoves( bitboards.Parameters, max_moves );
	int n_possible_moves = 0;
	all_moves( bitboards, moves_add, &n_possible_moves );

	root = newTree( moves_add, n_possible_moves );
	for( int n = 0; n < root->n_moves; n++ ) {
		//print_binary(root->moves_arr[n].parameters & 1); printf("\n");
	}

	cout << " Ender GEN\n";
	generator( bitboards, root, max_depth );

	//return;

	Move_Tree *head  = root;
	Move_Tree *child = nullptr;
	for( int n = 0; n < head->n_moves; n++ ) {
		print_binary(head->moves_arr[n].bitmove); printf("\n");
		cout<< "CHILDREN\n";
		child = head->moves_arr[n].children;
		cout << " #MOVES =" << child->n_moves << endl;
		for( int n = 0; n < child->n_moves; n++ ) {
			print_binary(child->moves_arr[n].bitmove); printf("\n");
		}
		printf("\n");
	}

	freeTree( root );

	return;
}

