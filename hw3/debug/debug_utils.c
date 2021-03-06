//#include "header.h"
// Surfaces
#define X0 0
#define X1 1
#define Y0 2
#define Y1 3
#define Z0 4
#define Z1 5

#define TRUE 1
#define FALSE 0

double timer(void)
{
	struct timeval time;
	gettimeofday(&time, 0);
	return time.tv_sec + time.tv_usec/1000000.0;
}

// is the region of mype an interior
int interior(int mype, int n_workers)
{
	int n_workers_axis  = (int) cbrt(n_workers);
	//assert((int)floor(n_workers_axis) == (int)n_workers_axis);
	int n2 = (int) pow(n_workers, 2);
	int n3 = (int) pow(n_workers, 3);
	int k  = (int) floor(mype / n2);

	if (mype < n2)
		return FALSE;
	else if (mype >= (n3 - n2))
		return FALSE;
	else if (mype % n_workers_axis == 0)
		return FALSE;
	else if ( (mype - (n_workers_axis-1)) % n_workers_axis == 0)
		return FALSE;
	else if ( (k*n2 <= mype) && (mype <= (k*n2 + n_workers_axis-1)) )
		return FALSE;
	else if ( ((k+1)*n2 - n_workers_axis <= mype) && (mype < (k+1)*n2) )
		return FALSE;
	else
		return TRUE;
}

// given mype and surface, exterior surface?
int exterior_surface(int mype, int n_workers, int surface)
{
	int n_workers_axis  = (int) cbrt(n_workers);
	//assert((int)floor(n_workers_axis) == (int)n_workers_axis);
	int n2 = (int) pow(n_workers_axis, 2);
	int n3 = (int) pow(n_workers_axis, 3);
	int k  = (int) floor(mype / n2);
	printf("n_workers_axis:%d, n2:%d, n3:%d, k:%d\n",
			n_workers_axis, n2, n3, k);

	// testing Z0
	if (mype < n2 && surface == Z0)
		return TRUE;
	else if (mype >= n3-n2 && surface == Z1)
		return TRUE;
	else if (mype % n_workers_axis == 0 && surface == X0)
		return TRUE;
	else if ((mype - (n_workers_axis-1)) % n_workers_axis == 0 && surface == X1)
		return TRUE;
	else if ((k*n2 <= mype) && (mype <= (k*n2 + n_workers_axis-1)) &&
			surface == Y1)
		return TRUE;
	else if (((k+1)*n2 - n_workers_axis <= mype) && (mype < (k+1)*n2) &&
			surface == Y0)
		return TRUE;
	else
		return FALSE;
}


