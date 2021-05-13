#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

#include "functions.h"
#include "global.h"
#include "initialize.h"

void print_depth2(Move_Tree*);
int count_moves(Move_Tree*);

void engine( ) {

        clock_t start = clock();

	//Move_Tree *root = nullptr;
	Move_Tree *root;

	//Find Depth 0
	Moves *moves_add = newMoves( bitboards.Parameters, max_moves );
	int n_possible_moves = 0;
	all_moves( bitboards, moves_add, &n_possible_moves );

	cout << " Ender GEN\n";
	root = newTree( moves_add, n_possible_moves );
	generator( bitboards, root, max_depth );

	cout << " Depth: " << max_depth + 1<< "\n";
	cout << " Time used: " << ( clock() - start ) / (double) CLOCKS_PER_SEC << "\n\n";

	//print_depth2( root );
	int total_moves = count_moves( root );
	cout << " Total Moves = " << total_moves << endl;

	freeTree( root );

	return;
}

int count_moves( Move_Tree *head ) {
	int counter = 0;
	for( int n = 0; n < head->n_moves; n++ ) {
		counter++;
		if( head->moves_arr[n].children != nullptr ) {
			counter += count_moves( head->moves_arr[n].children );
		}
	}
	return counter;
}

void print_depth2( Move_Tree *head ) {
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
	return;
}
