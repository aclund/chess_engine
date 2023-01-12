#include <time.h>
#include "functions.h"

void print_depth2(Move_Tree*);
int count_moves(Move_Tree*);
int count_bottom(Move_Tree*,int);

void perft( Chess_Board bitboards, Hash history ) {

        clock_t start = clock();

	cout << "\n Calculating... \n";

	//Find Depth 0
	Move_Tree *root = new Move_Tree;
	all_moves( bitboards, root->moves_arr );

	generator( bitboards, root, history, max_depth-1 );

        clock_t for_moves = clock();


	/*  Depth Printers
	//print_depth2( root->moves_arr[1].children );

	int c_moves;
	for( int n = 0; n < n_possible_moves; n++ ) {
		if( bitboards.Parameters & 1 ) {
			print_moves( &root->moves_arr[n], 1, bitboards.Black.All );
		}
		else {
			print_moves( &root->moves_arr[n], 1, bitboards.White.All );
		}

		if( max_depth == 2 ) { 
			c_moves = root->moves_arr[n].children->n_moves; }
		else { 
			c_moves = count_bottom( root->moves_arr[n].children, max_depth-1 );
		 }

		cout << "  " << c_moves << endl;
	}
	*/

	//print_moves( &root->moves_arr[mmm_tasty_spot], 1, n_print_pieces );


	int total_moves = count_moves( root );
	cout << " Total Moves = " << total_moves << endl;

	freeTree( root );

	cout << " Time used:  " << ( for_moves - start ) / (double) CLOCKS_PER_SEC << "\n\n";
	//cout << " Time used:  " << ( clock() - start ) / (double) CLOCKS_PER_SEC << "\n\n";


	return;
}

int count_moves( Move_Tree *head ) {
	int counter = 0;
	for( int n = 0; n < head->moves_arr.size(); n++ ) {
		counter++;
		if( head->moves_arr[n].children != NULL ) {
			counter += count_moves( head->moves_arr[n].children );
		}
	}
	return counter;
}

int count_bottom( Move_Tree *head, int depth ) {
	int counter = 0;
	for( int n = 0; n < head->moves_arr.size(); n++ ) {
		if( head->moves_arr[n].children != NULL ) {
			if( depth == 1 ) {
				counter += head->moves_arr[n].children->moves_arr.size();
			}
			else {
				counter += count_bottom( head->moves_arr[n].children, depth-1 );
			}
		}
	}
	return counter;
}

void print_depth2( Move_Tree *head ) {
	Move_Tree *child = NULL;
	for( int n = 0; n < head->moves_arr.size(); n++ ) {
		print_binary(head->moves_arr[n].bitmove); printf("\n");
		cout<< "CHILDREN\n";
		child = head->moves_arr[n].children;
		cout << " #MOVES =" << child->moves_arr.size() << endl;
		for( int n = 0; n < child->moves_arr.size(); n++ ) {
			print_binary(child->moves_arr[n].bitmove); printf("\n");
		}
		printf("\n");
	}
	return;
}
