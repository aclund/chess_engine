#include "functions.h"

void setup_mpi( int argc, char *argv[] ) {

	MPI_Init( &argc, &argv);
	MPI_Comm_size( MPI_COMM_WORLD, &num_procs );
	MPI_Comm_rank( MPI_COMM_WORLD, &myid      );

	l_root = false;
	if( myid == i_root ) l_root = true;
}
