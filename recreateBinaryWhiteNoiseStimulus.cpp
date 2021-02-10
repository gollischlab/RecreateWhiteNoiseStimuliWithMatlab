#include <mex.h>
#include <memory.h>
#include <matrix.h>
#include <math.h>

#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

double ran1(long &idum);	

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    if (nrhs < 3) mexErrMsgTxt("Input arguments are stixel width, stixel height, number of frames [and seed].");
    if (nrhs > 4) mexErrMsgTxt("Input arguments are stixel width, stixel height, number of frames [and seed].");
    if (nlhs != 1) mexErrMsgTxt("Wrong number of output arguments.");
    
    // input arguments
    int xstixels, ystixels, nframes; // required
    long seed = -10000; // optional with default value
    
    //get input data
	if (mxIsDouble(prhs[0])) xstixels = (int)mxGetScalar(prhs[0]);
	else mexErrMsgTxt("Invalid class of input argument 'xpixels'.");
    
	if (mxIsDouble(prhs[1])) ystixels = (int)mxGetScalar(prhs[1]);
	else mexErrMsgTxt("Invalid class of input argument 'ypixels'.");

	if (mxIsDouble(prhs[2])) nframes = (int)mxGetScalar(prhs[2]);
	else mexErrMsgTxt("Invalid class of input argument 'nframes'.");

    if (nrhs == 4) {
	  if (mxIsDouble(prhs[3])) {
          seed = (int)mxGetScalar(prhs[3]);
          if (seed > 0) seed = -seed;
      }
      else mexErrMsgTxt("Invalid class of input argument 'seed'.");
    }
    
    // create pointer array
    double *stimulus = new double[xstixels*ystixels*nframes];
    
	// generate array of random numbers
    for (int n=0; n<nframes; n++)
        for (int x=0; x<xstixels; x++)
			for (int y=0; y<ystixels; y++)
                stimulus[n*xstixels*ystixels + x*ystixels + y] = ran1( seed ) < 0.5 ? -1 : 1;
        
    // allocate space for output mxArray
    mwSize dims2[3] = {ystixels, xstixels, nframes};
    const mwSize *dims{ dims2 }; 
	plhs[0] = mxCreateNumericArray(3, dims, mxDOUBLE_CLASS, mxREAL);

    memcpy(mxGetPr(plhs[0]), stimulus, xstixels*ystixels*nframes*sizeof(double));
    
    // delete pointer array
    delete [] stimulus;
}


double ran1(long &idum)
{
	int j;
	long k;
	static long iy=0;
	static long iv[NTAB];
	double temp;

	if (idum <= 0 || !iy) {
		if (-(idum) < 1) idum=1;
		else idum = -(idum);
		for (j=NTAB+7;j>=0;j--) {
			k=(idum)/IQ;
			idum=IA*(idum-k*IQ)-IR*k;
			if (idum < 0) idum += IM;
			if (j < NTAB) iv[j] = idum;
		}
		iy=iv[0];
	}
	k=(idum)/IQ;
	idum=IA*(idum-k*IQ)-IR*k;
	if (idum < 0) idum += IM;
	j=iy/NDIV;
	iy=iv[j];
	iv[j] = idum;
	if ((temp=AM*iy) > RNMX) return RNMX;
	else return temp;
}
