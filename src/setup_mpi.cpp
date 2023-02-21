#include "functions.h"

void setup_mpi( int argc, char *argv[] ) {

#ifdef MPI_ON
	MPI_Init( &argc, &argv);
	MPI_Comm_size( MPI_COMM_WORLD, &num_procs );
	MPI_Comm_rank( MPI_COMM_WORLD, &myid      );
#else
	num_procs = 1;
	myid = i_root;
#endif

	l_root = false;
	if( myid == i_root ) l_root = true;
}
