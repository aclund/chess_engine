Compile    = g++
Libraries  =
#DebugFlag  = -g 
OPTFlag    = -O3
CHESSFiles  := $(shell ls *.cpp)
CHESSFiles  := $(filter-out randomer.cpp, $(CHESSFiles))
CHESSoFiles  = ${CHESSFiles:.cpp=.o}
RANDOMERFiles  := $(shell ls *.cpp)
RANDOMERFiles  := $(filter-out chess.cpp, $(RANDOMERFiles))
RANDOMERoFiles  = ${RANDOMERFiles:.cpp=.o}
HEADERFiles  = functions.h global.h piece_moves.h piece_moves.h check_check.h preform_move.h initialize.h
#HEADERFiles  = 

all: chess randomer

chess:  $(CHESSoFiles)
	$(Compile) -o chess  $(CHESSoFiles) $(OPTFlag) $(DebugFlag) $(Libraries)

randomer: $(RANDOMERoFiles)
	$(Compile) -o randomer  $(RANDOMERoFiles) $(OPTFlag) $(DebugFlag) $(Libraries)

$(CHESSoFiles): %.o: %.cpp $(HEADERFiles)
	$(Compile) $(OPTFlag) $(DebugFlag) -c $<

clean:
	rm -f *.o chess randomer
	touch *
