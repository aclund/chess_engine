#include "global.h"
#include "functions.h"
#include "convert_binary.h"

inline int rel_rank( int i, int i_turn ) {
        return int((1-i_turn)*4.5) + (int(i/8)+1)*i_turn;
}
inline int rel_col ( int i ) {
        return i - int(i/8)*8;
}
inline void add_promotes( Moves *moves_promote ) {
        // Reset curruent piece
        int n = 0;
        moves_promote[n].piece = -1*queen;
        n++;
        // Copy to other promote pieces
        moves_promote[n].bitmove = moves_promote[n-1].bitmove;
        moves_promote[n].piece   = -1*rook;
        n++;
        moves_promote[n].bitmove = moves_promote[n-1].bitmove;
        moves_promote[n].piece   = -1*bishop;
        n++;
        moves_promote[n].bitmove = moves_promote[n-1].bitmove;
        moves_promote[n].piece   = -1*knight;
        n++;
        if( moves_promote[n-4].capture ) {
                moves_promote[n-1].capture = true;
                moves_promote[n-2].capture = true;
                moves_promote[n-3].capture = true;
        }
}

int pawn_moves  ( Moves *moves_add, uint64_t pawns,   uint64_t their_pieces, uint64_t not_all_pieces, uint64_t not_pinned,
                  int t_en_passant, int i_turn ) {
        int n_moves = 0;

        int indices[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
        convert_binary( pawns, indices );

        int i = 0, index_update, pawn_rank, pawn_col;
        while( indices[i] != -1 ) {
                if( (not_pinned >> indices[i]) & 1 ) {
                        pawn_rank = rel_rank( indices[i], i_turn );
                        pawn_col  = rel_col ( indices[i] );
//cout << " pawn rank, col " << indices[i] << ":"<< pawn_rank << "  " << pawn_col <<"\n";

                        index_update = indices[i] +  8*i_turn;    // Square in front
                        if( (not_all_pieces >> index_update) & 1 ) {

                                BIT_SET(moves_add[n_moves].bitmove, indices[i]);
                                BIT_SET(moves_add[n_moves].bitmove, index_update);
                                moves_add[n_moves].piece = pawn;
                                n_moves++;
                                if( pawn_rank == 7 ) { // Promote
                                        add_promotes( &moves_add[n_moves-1] );
                                        n_moves += 3;
                                }
                        }

                        if( pawn_col != 0 ) {
                                index_update = indices[i] +  7*i_turn; // Capturable left
                                if( (their_pieces >> index_update) & 1 ) {
                                        BIT_SET(moves_add[n_moves].bitmove, indices[i]);
                                        BIT_SET(moves_add[n_moves].bitmove, index_update);
                                        moves_add[n_moves].piece   = pawn;
                                        moves_add[n_moves].capture = true;
                                        n_moves++;
                                        if( pawn_rank == 7 ) { // Promote
                                                add_promotes( &moves_add[n_moves-1] );
                                                n_moves += 3;
                                        }
                                }
                                else if( t_en_passant == index_update ) {
                                        BIT_SET(moves_add[n_moves].bitmove, indices[i]);
                                        BIT_SET(moves_add[n_moves].bitmove, index_update);
                                        moves_add[n_moves].piece   = en_passant;
                                        moves_add[n_moves].capture = true;
//cout << en_passant << "SET take en passant " << t_en_passant << endl;
                                        n_moves++;
                                        if( pawn_rank == 7 ) { // Promote
                                                add_promotes( &moves_add[n_moves-1] );
                                                n_moves += 3;
                                        }
                                }
                        }

                        if( pawn_col != 7 ) {
                                index_update = indices[i] +  9*i_turn; // Capturable right
                                if( (their_pieces >> index_update) & 1 ) {
                                        BIT_SET(moves_add[n_moves].bitmove, indices[i]);
                                        BIT_SET(moves_add[n_moves].bitmove, index_update);
                                        moves_add[n_moves].piece   = pawn;
                                        moves_add[n_moves].capture = true;
                                        n_moves++;
                                        if( pawn_rank == 7 ) { // Promote
                                                add_promotes( &moves_add[n_moves-1] );
                                                n_moves += 3;
                                        }
                                }
                                else if( t_en_passant == index_update ) {
                                        BIT_SET(moves_add[n_moves].bitmove, indices[i]);
                                        BIT_SET(moves_add[n_moves].bitmove, index_update);
                                        moves_add[n_moves].piece   = en_passant;
                                        moves_add[n_moves].capture = true;
//cout << en_passant << "SET take en passant " << t_en_passant << endl;
//cout << i_turn << " turn " << index_update <<endl;
                                        n_moves++;
                                        if( pawn_rank == 7 ) { // Promote
                                                add_promotes( &moves_add[n_moves-1] );
                                                n_moves += 3;
                                        }
                                }
                        }
//if( indices[i] == 51 ) { cout << " Pawn found 51... " << pawn_rank << " " << pawn_col << endl; }
//if( index_update == 58 or index_update == 60 ) { cout << index_update << "  rank:"<<pawn_rank << endl; }

                        if(      pawn_rank == 2 ) {
                                index_update = indices[i] + 16*i_turn; // Up two beginning
                                if( ((not_all_pieces >> index_update         ) & 1) &&
                                    ((not_all_pieces >> (indices[i]+8*i_turn)) & 1) ) {

                                        BIT_SET(moves_add[n_moves].bitmove, indices[i]);
                                        BIT_SET(moves_add[n_moves].bitmove, index_update);
                                        moves_add[n_moves].piece = pawn;
                                        // Set en_passant
                                        int bit2 = 32, temp_passant = indices[i]+8*i_turn, i = 5;
                                        while( temp_passant != 0 and bit2 != 0 ) {
                                                if( int(temp_passant/bit2) ) {
                                                        BIT_SET(moves_add[n_moves].parameters,i);
                                                        temp_passant -= bit2;
                                                }
                                                i++;
                                                bit2 /= 2;
                                        }
                                        n_moves++;
                                }
                        }

                }
                i++;
        }

        return n_moves;
}
