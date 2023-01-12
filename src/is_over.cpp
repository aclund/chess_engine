#include "functions.h"

void is_over( Chess_Board bitboards, Hash history, int i_turn_counter ) {

        write_board( bitboards );

        cout << " Move #" << i_turn_counter << endl;

	// 3 fold repetition
	if( history.rep3fold() ) {
		cout << " DRAWN by THREEFOLD REPETITION! \n\n";
		return;
	}

        uint32_t half_clock = bitboards.Parameters;
        half_clock %= 4096;
        BIT_CLEAR( half_clock, 0 );
        BIT_CLEAR( half_clock, 1 );
        BIT_CLEAR( half_clock, 2 );
        BIT_CLEAR( half_clock, 3 );
        BIT_CLEAR( half_clock, 4 );
        if( half_clock >= 3200 ) { cout << "50 Move STALEMATE! \n\n"; return; }

        int i_turn;
        Pieces *your_pieces, *their_pieces;
        switch( bitboards.Parameters & 1 ) {
          case 0: // White to Move
                your_pieces  = &bitboards.White;
                their_pieces = &bitboards.Black;
                i_turn = 1;
          break;
          case 1: // Black to Move
                your_pieces  = &bitboards.Black;
                their_pieces = &bitboards.White;
                i_turn = -1;
          break;
        }

        int n_checks = 0;
        check_check( your_pieces->King, your_pieces->All, their_pieces,
                     ~bitboards.All_Pieces, i_turn, &n_checks );

        if( n_checks == 0 ) {
                cout << " STALEMATE! \n\n";
        }
        else {
                cout << " CHECKMATE! \n\n";
        }

        return;
}
