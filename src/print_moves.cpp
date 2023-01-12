#include "functions.h"

void print_moves( Moves *moves_print, int n_moves, uint64_t your_pieces ) {

        cout << "- Last Move -\n";

        for( int n = 0; n < n_moves; n++ ) {
                //cout << " " << n+1 << ":  ";
                if( moves_print[n].piece == 7 ) {
                        if(      (moves_print[n].bitmove >>  7) & 1 ) { // K
                                cout << "White Castle King\n";
                        }
                        else if( (moves_print[n].bitmove >>  0) & 1 ) { // Q
                                cout << "White Castle Quenn\n";
                        }
                        else if( (moves_print[n].bitmove >> 63) & 1 ) { // k
                                cout << "Black Castle King\n";
                        }
                        else if( (moves_print[n].bitmove >> 56) & 1 ) { // q
                                cout << "Black Castle Quenn\n";
                        }
                  	break;
                }
                switch( moves_print[n].piece ) {
                  case 1: // PAWN
                        cout << " Pawn";
                  break;
                  case 12:// EN PASSANT
                        cout << " En Passant";
                  break;
                  case 2: // KNIGHT
                        cout << " Knight";
                  break;
                  case 3: // BISHOP
                        cout << " Bishop";
                  break;
                  case 4: // ROOK
                        cout << " Rook";
                  break;
                  case 5: // QUEEN
                        cout << " Queen";
                  break;
                  case 6: // KING
                        cout << " King";
                  break;
                  case 8:// PROMOTE Knight
                        cout << " PROMOTE 2 Knight";
                  break;
                  case 9:// PROMOTE Bishop
                        cout << " PROMOTE 2 Bishop";
                  break;
                  case 10:// PROMOTE Rook
                        cout << " PROMOTE 2 Rook";
                  break;
                  case 11:// PROMOTE Queen
                        cout << " PROMOTE 2 Queen";
                  break;

                  default:
                        cout << " ERROR printing move...?\n";
                  break;
                }

        	int index;
		convert_binary( (moves_print[n].bitmove & ~your_pieces), &index );
                cout << index2square(index);
                cout << "\n";

		//print_binary(moves_print[n].bitmove); cout << endl;
        }
        return;
}
