#include <iostream>
using namespace std;

#include "global.h"
#include "functions.h"

int check_bits( Chess_Board chess_board ) {
	int ierr = 0;

	//Check that no pieces overlap...
	if((chess_board.White.Pawns   & chess_board.White.Knights &
	    chess_board.White.Bishops & chess_board.White.Rooks   &
	    chess_board.White.Queens  & chess_board.White.King    &
	    chess_board.Black.Pawns   & chess_board.Black.Knights &
	    chess_board.Black.Bishops & chess_board.Black.Rooks   &
	    chess_board.Black.Queens  & chess_board.Black.King    )
	    != 0 ) {
		cout << " ERROR Pieces overlap!\n";
		ierr = 1;
	}
	
	
	//Color.All == &all
	if((chess_board.White.Pawns   ^ chess_board.White.Knights ^
	    chess_board.White.Bishops ^ chess_board.White.Rooks   ^
	    chess_board.White.Queens  ^ chess_board.White.King    ) !=
	    chess_board.White.All ) {
		cout << " ERROR White.All ~= ^all!\n";
		ierr = 1;
	}
	if((chess_board.Black.Pawns   ^ chess_board.Black.Knights ^
	    chess_board.Black.Bishops ^ chess_board.Black.Rooks   ^
	    chess_board.Black.Queens  ^ chess_board.Black.King    ) !=
	    chess_board.Black.All ) {
		cout << " ERROR Black.All ~= ^all!\n";
		ierr = 1;
	}

	//All_Pieces
 	if( (chess_board.White.All ^ chess_board.Black.All) !=
	     chess_board.All_Pieces ) {
		print_binary( chess_board.All_Pieces ); cout << " All pieces\n";
		print_binary( chess_board.White.All  ); cout << " White All pieces\n";
		print_binary( chess_board.Black.All  ); cout << " Black All pieces\n";
		cout << " ERROR bits All_Pieces!\n";
		ierr = 1;
		if( (chess_board.White.All | chess_board.Black.All) !=
		     chess_board.All_Pieces ) {
			cout << " ERROR bits All_Pieces overlap!\n";
			ierr = 1;
		}
	}

	return ierr;
}
