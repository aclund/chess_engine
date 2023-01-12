#include "functions.h"

void stop_on_error( int ierr ) {

	int ierr_max;
	MPI_Allreduce( &ierr, &ierr_max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD );

	if( ierr_max != 0 ) { MPI_Abort( MPI_COMM_WORLD, 1 ); }
}
