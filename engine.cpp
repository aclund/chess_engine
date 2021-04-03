#include <iostream>
#include <math.h>
#include <time.h>

using namespace std;

#include "functions.h"
#include "global.h"

void add_mem( int **possible_boards, int *max_tree, int size_add ) {

	cout << *max_tree<<endl;
	size_t newSize = *max_tree + size_add;
    	int **newArr = new int*[newSize];
	for( int i = 0; i < newSize; i++ ) {
		newArr[i] = new int[64]; 
	}

	memcpy( newArr, possible_boards, *max_tree * sizeof(int) );

	for( int i = 0; i < *max_tree; i++ ) {
		delete [] possible_boards[i];
	}
	delete [] possible_boards;

   	*max_tree = newSize;
	for( int i = 0; i < newSize; i++ ) {
		possible_boards[i] = newArr[i]; 
	}
	cout << *max_tree<<endl;
	cout << possible_boards[0][0] << endl;
	cout << " ALLOCATED MEMORY\n";
	return;
}


void engine() {

	int i_start_depth[max_depth];
	int i_end_depth  [max_depth];
	clock_t start;
	double duration;

	// Load board into temporary for some reason then find every possible move
	const int i_64 = 64;
	const int i_6  = 6;
	int max_tree = 11111111;
	int size_add = 2;
	int **possible_boards;
	int **all_params;
	possible_boards = (int **)malloc(sizeof(int * )*max_tree);
	all_params      = (int **)malloc(sizeof(int * )*max_tree);
	for( int i = 0; i < max_tree; i++ ) {
		possible_boards[i] = (int *)malloc(sizeof(int) *i_64);
		all_params[i]      = (int *)malloc(sizeof(int) *i_6 );
	}

	// Set current board
	int count = 0;
	for( int row = 0; row < 8; row++ ) {
		for( int col = 0; col < 8; col++ ) {
			possible_boards[0][count] = board[row][col];
			count++;
		}
	}

	// Find depth 0
	n_possible_moves = 0;
	all_moves(possible_boards[0], params, &possible_boards[1], turn);

	int i_start = 1;
	int i_end   = i_start + n_possible_moves;
	cout << " There are " << i_end - i_start << " possible moves!\n\n";

	// Find all moves in depth
	int engine_board = 0;
	int move_counter = 0;
	int i_open = n_possible_moves + 1;
	int i_turn = turn;

	for( int depth = 0; depth < max_depth; depth++ ) {

		start = clock();

		i_turn *= -1;
		for( int i = i_start; i < i_end; i++ ) {
			//write_from2d(&possible_boards[i]);

			//all_moves(possible_boards[i], &params[i], &possible_boards[i_open], i_turn);
			all_moves(possible_boards[i], params, &possible_boards[i_open], i_turn);

			i_open = n_possible_moves + 1;

			if( (max_tree - i_open) < 100 ) { // Could run out of memory next board
				max_tree *= size_add;
				possible_boards = (int **)realloc(possible_boards, sizeof(int **)*max_tree);
				all_params      = (int **)realloc(possible_boards, sizeof(int **)*max_tree);
				for( int i = max_tree/size_add; i < max_tree; i++ ) {
					possible_boards[i] = (int *)malloc(sizeof(int) *i_64);
					all_params[i]      = (int *)malloc(sizeof(int) *i_6 );
				}
			}
		}
		i_start = i_end;
		i_end   = n_possible_moves + 1;
		i_start_depth[depth] = i_start;
		i_end_depth  [depth] = i_end;
		cout << " move " << (depth+1) << " # Possible Moves = " << i_end - i_start << "\n";
		cout << " Time used: " << ( clock() - start ) / (double) CLOCKS_PER_SEC << "\n\n";

	}

	//int alpha, beta;
	//int score = minimax( possible_boards, max_depth, alpha, beta, true );
	//cout << " Score Evaluation = " << score << "\n";

	/*
	int i_spot;
	for( int i = i_start_depth[max_depth-1]; i < i_end_depth[max_depth-1]; i++ ) {
		if( turn*board_scores[i] > engine_board ) {
			engine_board = turn*board_scores[i];
			i_spot = i;
		}
		//engine_board = max(engine_board, turn*board_scores[i]);
	}
	//for( int i = i_start_depth[
	*/

	// Update board with best move
	int index = 0;
	for( int row = 0; row < 8; row++ ) {
		for( int col = 0; col < 8; col++ ) {
			board[row][col] = possible_boards[engine_board][index];
			index++;
		}
	}

	// Save best moves
	//save_boards( possible_boards, scores );

	// Delete tree
	//cout << max_tree;
	for( int i = 0; i < max_tree; i++ ) {
		delete [] possible_boards[i];
		delete [] all_params[i];
	}
	delete [] possible_boards;
	delete [] all_params;

	return;
}
