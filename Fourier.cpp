#include <stdio.h>
#include "Fourier.h"
#include "ArrayGenerator.h"
#include "Parameter.h"
#include "Source.h"
using namespace std;

Fourier::Fourier(int SourceMode) {
	Source source;

	//Sine Wave
	if( SourceMode == 1 ) {
		int T = source.getsourcePeriod();
		int q = source.getstepPerPeriod();
		fourier_start = (T - 1) * q;
		fourier_end   = fourier_start + q;
	}
	//Gaussian Pulse
	else if( SourceMode == 2 ) {
		int totaltime = source.gettotaltime();
		fourier_start = 0;
		fourier_end   = totaltime;
	}

	//int m1=(int)round(f_min / df);			// The start grid of frequency step in freq domain
	//int m2=(int)round(f_max / df),			// The end grid of frequency step in freq domain
	//int m0=(int)round(f0    / df);			// The pitch grid of frequency step in freq domain

	// For phasor
	register int f;

	double *frequency_G = new double [frequency_sample],
	     *omega_G     = new double [frequency_sample];
	for(f=0;f<frequency_sample;f++)
	{ frequency_G[f] = (m1+f)*df; // => m1*df + f*df => (f_min + f*df)
	omega_G[f]     = 2.0*PI*frequency_G[f]; }

	double *lambda_G = new double [frequency_sample];
	for(f=0;f<frequency_sample;f++)
	{ lambda_G[f] = c / frequency_G[f]; }


	Alloc3DArray();

}

void Fourier::Alloc3DArray() {
	Parameter param;
	int SIZE_X = param.SIZE_X;
	int SIZE_Y = param.SIZE_Y;
	int SIZE_Z = param.SIZE_Z;

	ArrayGenerator generator;

	Ex_phasor_sin 	= generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y, SIZE_Z);
	Ex_phasor_cos 	= generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y, SIZE_Z);
	abs_Ex_phasor 	= generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y, SIZE_Z);
	Ex_phase 		= generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y, SIZE_Z);

	Ey_phasor_sin 	= generator.Alloc3DArray_double(SIZE_X, SIZE_Y-1, SIZE_Z);
	Ey_phasor_cos 	= generator.Alloc3DArray_double(SIZE_X, SIZE_Y-1, SIZE_Z);
	abs_Ey_phasor 	= generator.Alloc3DArray_double(SIZE_X, SIZE_Y-1, SIZE_Z);
	Ey_phase 		= generator.Alloc3DArray_double(SIZE_X, SIZE_Y-1, SIZE_Z);

	Ez_phasor_sin 	= generator.Alloc3DArray_double(SIZE_X, SIZE_Y, SIZE_Z-1);
	Ez_phasor_cos 	= generator.Alloc3DArray_double(SIZE_X, SIZE_Y, SIZE_Z-1);
	abs_Ez_phasor 	= generator.Alloc3DArray_double(SIZE_X, SIZE_Y, SIZE_Z-1);
	Ez_phase 		= generator.Alloc3DArray_double(SIZE_X, SIZE_Y, SIZE_Z-1);

	Hx_phasor_sin 	= generator.Alloc3DArray_double(SIZE_X, SIZE_Y-1, SIZE_Z-1);
	Hx_phasor_cos 	= generator.Alloc3DArray_double(SIZE_X, SIZE_Y-1, SIZE_Z-1);
	abs_Hx_phasor 	= generator.Alloc3DArray_double(SIZE_X, SIZE_Y-1, SIZE_Z-1);
	Hx_phase 		= generator.Alloc3DArray_double(SIZE_X, SIZE_Y-1, SIZE_Z-1);

	Hy_phasor_sin 	= generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y, SIZE_Z-1);
	Hy_phasor_cos 	= generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y, SIZE_Z-1);
	abs_Hy_phasor 	= generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y, SIZE_Z-1);
	Hy_phase 		= generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y, SIZE_Z-1);

	Hz_phasor_sin 	= generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y-1, SIZE_Z);
	Hz_phasor_cos 	= generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y-1, SIZE_Z);
	abs_Hz_phasor 	= generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y-1, SIZE_Z);
	Hz_phase 		= generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y-1, SIZE_Z);
}

Fourier::~Fourier() {
	Parameter param;
	int SIZE_X = param.SIZE_X;
	int SIZE_Y = param.SIZE_Y;

	for( int i = 0; i < SIZE_X; i++ ) {
		for( int j = 0; j < SIZE_Y; j++ ) {
			if( i != SIZE_X-1 ) { 
				// Ex
				delete[] Ex_phasor_sin[i][j];
				delete[] Ex_phasor_cos[i][j];
				delete[] abs_Ex_phasor[i][j];
				delete[] Ex_phase[i][j];
				// Hy
				delete[] Hy_phasor_sin[i][j];
				delete[] Hy_phasor_cos[i][j];
				delete[] abs_Hy_phasor[i][j];
				delete[] Hy_phase[i][j];
			}
			if( j != SIZE_Y-1 ) {
				// Ey
				delete[] Ey_phasor_sin[i][j];
				delete[] Ey_phasor_cos[i][j];
				delete[] abs_Ey_phasor[i][j];
				delete[] Ey_phase[i][j];
				// Hx
				delete[] Hx_phasor_sin[i][j];
				delete[] Hx_phasor_cos[i][j];
				delete[] abs_Hx_phasor[i][j];
				delete[] Hx_phase[i][j];
			}
			// Ez
			delete[] Ez_phasor_sin[i][j];
			delete[] Ez_phasor_cos[i][j];
			delete[] abs_Ez_phasor[i][j];
			delete[] Ez_phase[i][j];
			if( i != SIZE_X-1 && j != SIZE_Y-1 ) {
				// Hz
				delete[] Hz_phasor_sin[i][j];
				delete[] Hz_phasor_cos[i][j];
				delete[] abs_Hz_phasor[i][j];
				delete[] Hz_phase[i][j];
			}
		}
		if( i != SIZE_X-1 ) {
			// Ex
			delete[] Ex_phasor_sin[i];
			delete[] Ex_phasor_cos[i];
			delete[] abs_Ex_phasor[i];
			delete[] Ex_phase[i];
			// Hy
			delete[] Hy_phasor_sin[i];
			delete[] Hy_phasor_cos[i];
			delete[] abs_Hy_phasor[i];
			delete[] Hy_phase[i];
			// Hz
			delete[] Hz_phasor_sin[i];
			delete[] Hz_phasor_cos[i];
			delete[] abs_Hz_phasor[i];
			delete[] Hz_phase[i];
		}
		// Ey
		delete[] Ey_phasor_sin[i];
		delete[] Ey_phasor_cos[i];
		delete[] abs_Ey_phasor[i];
		delete[] Ey_phase[i];
		// Ez
		delete[] Ez_phasor_sin[i];
		delete[] Ez_phasor_cos[i];
		delete[] abs_Ez_phasor[i];
		delete[] Ez_phase[i];
		// Hx
		delete[] Hx_phasor_sin[i];
		delete[] Hx_phasor_cos[i];
		delete[] abs_Hx_phasor[i];
		delete[] Hx_phase[i];
	}
	// Ex
	delete[] Ex_phasor_sin; Ex_phasor_sin = NULL;
	delete[] Ex_phasor_cos; Ex_phasor_cos = NULL;
	delete[] abs_Ex_phasor; abs_Ex_phasor = NULL;
	delete[] Ex_phase; Ex_phase = NULL;
	// Ey
	delete[] Ey_phasor_sin; Ey_phasor_sin = NULL;
	delete[] Ey_phasor_cos; Ey_phasor_cos = NULL;
	delete[] abs_Ey_phasor; abs_Ey_phasor = NULL;
	delete[] Ey_phase; Ey_phase = NULL;
	// Ez
	delete[] Ez_phasor_sin; Ez_phasor_sin = NULL;
	delete[] Ez_phasor_cos; Ez_phasor_cos = NULL;
	delete[] abs_Ez_phasor; abs_Ez_phasor = NULL;
	delete[] Ez_phase; Ez_phase = NULL;
	// Hx
	delete[] Hx_phasor_sin; Hx_phasor_sin = NULL;
	delete[] Hx_phasor_cos; Hx_phasor_cos = NULL;
	delete[] abs_Hx_phasor; abs_Hx_phasor = NULL;
	delete[] Hx_phase; Hx_phase = NULL;
	// Hy
	delete[] Hy_phasor_sin; Hy_phasor_sin = NULL;
	delete[] Hy_phasor_cos; Hy_phasor_cos = NULL;
	delete[] abs_Hy_phasor; abs_Hy_phasor = NULL;
	delete[] Hy_phase; Hy_phase = NULL;
	// Hz
	delete[] Hz_phasor_sin; Hz_phasor_sin = NULL;
	delete[] Hz_phasor_cos; Hz_phasor_cos = NULL;
	delete[] abs_Hz_phasor; abs_Hz_phasor = NULL;
	delete[] Hz_phase; Hz_phase = NULL;
}

void FT_SineWave(double ***Ex, double ***Ey, double ***Ez,
				 double ***Hx, double ***Hy, double ***Hz,
				 double *ex,   double *hy,   int t         ) {
	Parameter param;
	int SIZE_X = param.SIZE_X;
	int SIZE_Y = param.SIZE_Y;
	int SIZE_Z = param.SIZE_Z;

	if( t > fourier_start && t <= fourier_end ) {

		for( int i = 0; i < SIZE_X-1; i++ )
			for( int j = 0; j < SIZE_Y; j++ )
				for( int k = 0; k < SIZE_Z; k++ ) {
					Ex_phasor_sin[i][j][k] += Ex[i][j][k] * sin(omega*dt*t);
					Ex_phasor_cos[i][j][k] += Ex[i][j][k] * cos(omega*dt*t);

					// Modify fields because of the source
					if( (i>=startX && i<=endX) && (j>=startY+1 && j<=endY ) && (k>=startZ && k<=endZ) ) {
						Ex_phasor_sin[i][j][k] -= ex[k] * sin(omega*dt*t);
						Ex_phasor_cos[i][j][k] -= ex[k] * cos(omega*dt*t);
					}
		}
		for( int i = 0; i < SIZE_X; i++ )
			for( int j = 0; j < SIZE_Y-1; j++ )
				for( int k = 0; k < SIZE_Z; k++ ) {
					Ey_phasor_sin[i][j][k] += Ey[i][j][k] * sin(omega*dt*t);
					Ey_phasor_cos[i][j][k] += Ey[i][j][k] * cos(omega*dt*t);
		}
		for( int i = 0; i < SIZE_X; i++ )
			for( int j = 0; j < SIZE_Y; j++ )
				for( int k = 0; k < SIZE_Z-1; k++ ) {
					Ez_phasor_sin[i][j][k] += Ez[i][j][k] * sin(omega*dt*t);
					Ez_phasor_cos[i][j][k] += Ez[i][j][k] * cos(omega*dt*t);
		}
		for( int i = 0; i < SIZE_X; i++ )
			for( int j = 0; j < SIZE_Y-1; j++ )
				for( int k = 0; k < SIZE_Z-1; k++ ) {
					Hx_phasor_sin[i][j][k] += Hx[i][j][k] * sin(omega*dt*t);
					Hx_phasor_cos[i][j][k] += Hx[i][j][k] * cos(omega*dt*t);
		}
		for( int i = 0; i < SIZE_X-1; i++ )
			for( int j = 0; j < SIEZ_Y; j++ )
				for( int k = 0; k < SIZE_Z-1; k++ )	{
					Hy_phasor_sin[i][j][k] += Hy[i][j][k] * sin(omega*dt*t);
					Hy_phasor_cos[i][j][k] += Hy[i][j][k] * cos(omega*dt*t);
		
					// Modify fields because of the source
					if( (i>=startX && i<=endX) && (j>=startY+1 && j<=endY) && (k>=startZ && k<=endZ-1) ) {
						Hy_phasor_sin[i][j][k] -= hy[k] * sin(omega*dt*t);
						Hy_phasor_cos[i][j][k] -= hy[k] * cos(omega*dt*t);
					}
		}
		for( int i = 0; i < SIZE_X-1; i++ )
			for( int j = 0; j < SIZE_Y-1; j++ )
				for( int k = 0; k < SIZE_Z; k++ ) {
					Hz_phasor_sin[i][j][k] += Hz[i][j][k] * sin(omega*dt*t);
					Hz_phasor_cos[i][j][k] += Hz[i][j][k] * cos(omega*dt*t);
		}
		    
		ex_Re += ex[startZ] * sin(omega*t*dt)*dt;
		ex_Im += ex[startZ] * cos(omega*t*dt)*dt;

		hy_Re += hy[startZ] * cos(omega*t*dt)*dt;
		hy_Im += hy[startZ] * sin(omega*t*dt)*dt;

	}

}

void FT_GaussianWave() {

}