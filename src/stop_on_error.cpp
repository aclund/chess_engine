#include "functions.h"

void stop_on_error( int ierr ) {

	int ierr_max;
#ifdef MPI_ON
	MPI_Allreduce( &ierr, &ierr_max, 1, MPI_INT, MPI_MAX, MPI_COMM_WORLD );
#else
	ierr_max = ierr;
#endif

	if( ierr_max != 0 ) {
#ifdef MPI_ON
		MPI_Finalize( );
#endif
		exit( 0 );
	}
}
