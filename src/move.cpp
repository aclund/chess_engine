#include "functions.h"
#include "sstream"

string removechar( string str, char x ) {
   string result;
   for( size_t i=0; i<str.size(); i++ ) {
      char curr = str[i];
      if( curr != x ) {
         result += curr;
      }
   }
   return result;
} 

void move( Chess_Board *bitboards ) {

	// Find Possible Moves
	vector<Moves> moves_arr;
	all_moves( *bitboards, moves_arr );
	if( moves_arr.size() == 0 ) { return; }

	int target = 0, ierr = 0;
	if( l_root ) {

		// Prompt User
		string move_AN;
		for( string line; cout << "Enter move: " && getline(cin,line) && cout << "\n"; ) {
			istringstream iss(line);
			if( iss >> move_AN >> ws && iss.get() == EOF ) {
				if( move_AN == "exit" || move_AN == "quit" || move_AN == "ff" ) { ierr = 1; goto QUIT; }
				move_AN = removechar( move_AN, ' ' );
				move_AN = removechar( move_AN, 'x' );

				// Check validity and break
				ierr = valid_move( *bitboards, move_AN, moves_arr, &target );
				if( ierr == 0 ) break;
			}
			cout << "Either I suck at coding or you've forgotten the rules of CHESS!\n";
			cout << "Enter move in Algebraic Notation (nf3  Qd1  o-o  rfd1) \n\n";
		}

		// Print move
		uint64_t print_pieces;
		if( bitboards->Parameters & 1 ) { print_pieces = bitboards->Black.All; }
		else                            { print_pieces = bitboards->White.All; }
		print_moves( &moves_arr[target], 1, print_pieces );
	}
	QUIT:stop_on_error( ierr );

	// Preform move
#ifdef MPI_ON
	MPI_Bcast( &target, 1, MPI_INT, i_root, MPI_COMM_WORLD );
#endif
	*bitboards = preform_move( *bitboards, moves_arr[target] );

	return;
}
