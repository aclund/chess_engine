#include "functions.h"

string removeSpaces(string str)  
{ 
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
    str.erase(remove(str.begin(), str.end(), 'x'), str.end()); 
    return str; 
} 

void move( Chess_Board *bitboards ) {

	// Find Possible Moves
	vector<Moves> moves_arr;
	all_moves( *bitboards, moves_arr );
	if( moves_arr.size() == 0 ) { return; }

	string move_AN;
	int ierr = 1, target;
	while( ierr != 0 ) {
		cout << "Enter move\n\n";
		cin  >> move_AN;
		cout << "\n";
		move_AN = removeSpaces(move_AN);
	
		ierr = valid_move( *bitboards, move_AN, moves_arr, &target );
		if( ierr == 0 ) break;

		cout << "Either I suck at coding or you've forgotten the rules of CHESS!\n\n";
		cout << "Enter move in Algebraic Notation:\n";
		cout << "   nf3  Qd1  o-o  rfd1\n\n\n";
		move_AN.clear();
	}

	uint64_t print_pieces;
	if( bitboards->Parameters & 1 ) { print_pieces = bitboards->Black.All; }
	else 				{ print_pieces = bitboards->White.All; }
	print_moves( &moves_arr[target], 1, print_pieces );
	*bitboards = preform_move( *bitboards, moves_arr[target] );

	return;
}
