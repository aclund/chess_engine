Compile    = g++
Libraries  =
DebugFlag  = -g 
OPTFlag    = 
#CHESSFiles   = chess.cpp global.cpp write_board.cpp move.cpp valid_move.cpp index_square.cpp convert_fen.cpp set_moves.cpp
CHESSFiles  := $(shell ls *.cpp)
CHESSoFiles  = ${CHESSFiles:.cpp=.o}
HEADERFiles  = functions.h global.h colormod.h

all: chess

chess:  $(CHESSoFiles)
	$(Compile) -o chess  $(CHESSoFiles) $(OPTFlag) $(DebugFlag) $(Libraries)

$(CHESSoFiles): %.o: %.cpp $(HEADERFiles)
	$(Compile) $(DebugFlag) -c $<

clean:
	rm -f *.o chess
	touch *
