#include <iostream>
using namespace std;

#include "functions.h"
#include "global.h"
#include "convert_binary.h"
#include "initialize.h"
#include "piece_moves.h"
#include "check_check.h"

void is_over( Chess_Board chess_board, int i_turn_counter ) {

        convert2board( );
        write_board( board, params );

        cout << " Move #" << i_turn_counter << endl;

        uint32_t half_clock = chess_board.Parameters;
        half_clock %= 4096;
        BIT_CLEAR( half_clock, 0 );
        BIT_CLEAR( half_clock, 1 );
        BIT_CLEAR( half_clock, 2 );
        BIT_CLEAR( half_clock, 3 );
        BIT_CLEAR( half_clock, 4 );
        if( half_clock >= 3200 ) { cout << "50 Move STALEMATE! \n\n"; return; }

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
        //Moves_temp *check_pieces = newTemp(2);
        check_check( your_pieces->King, your_pieces->All, their_pieces,
                     ~chess_board.All_Pieces, i_turn, &n_checks );
                     //~chess_board.All_Pieces, i_turn, check_pieces, &n_checks );

        if( n_checks == 0 ) {
                cout << " STALEMATE! \n\n";
        }
        else {
                cout << " CHECKMATE! \n\n";
        }

        //delete[] check_pieces;
        return;
}
