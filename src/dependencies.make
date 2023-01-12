PROGRAMS = chess randomer

chess: all_moves.o ask_user.o check_bits.o check_check.o chess.o convert2bits.o convert2board.o convert_fen.o engine.o functions.o game_over.o global.o in_check.o initial_position.o initialize.o is_over.o last_known_board.o minimax.o move.o piece_tables.o preform_move.o print_moves.o random_player.o set_moves.o setup_mpi.o stop_on_error.o valid_move.o write_board.o

randomer: all_moves.o check_bits.o check_check.o convert2bits.o convert2board.o convert_fen.o functions.o game_over.o global.o in_check.o initial_position.o initialize.o is_over.o last_known_board.o piece_tables.o preform_move.o print_moves.o random_player.o randomer.o set_moves.o write_board.o
