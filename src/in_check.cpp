#include "functions.h"

bool in_check( Chess_Board chess_board ) {

        int i_turn;
        Pieces *your_pieces, *their_pieces;
        switch( chess_board.Parameters & 1 ) {
          case 0: // White to Move
                your_pieces  = &chess_board.White;
                their_pieces = &chess_board.Black;
                i_turn = 1;
          break;
          case 1: // Black to Move
                your_pieces  = &chess_board.Black;
                their_pieces = &chess_board.White;
                i_turn = -1;
          break;
        }

        int n_checks = 0;
        check_check( your_pieces->King, your_pieces->All, their_pieces,
                     ~chess_board.All_Pieces, i_turn, &n_checks );

        if( n_checks == 0 ) {
                return false;
        }
        else {
                return true;
        }
}
