#include <stdio.h>
#include <cmath>
#include "Fourier.h"
#include "ArrayGenerator.h"
using namespace std;

Fourier::Fourier() {
	//Sine Wave
	if( SourceMode == 1 ) {
		fourier_start = (sourcePeriod - 1) * stepPerPeriod;
		fourier_end   = fourier_start + stepPerPeriod;
	
		AllocPhasorForSine();
	}
	//Gaussian Pulse
	else if( SourceMode == 2 ) {
		fourier_start = 0;
		fourier_end   = totaltime;

		ArrayGenerator generator;
		GaussianFreq 		= generator.Alloc1DArray_double(frequency_sample+1);
		GaussianAngularFreq = generator.Alloc1DArray_double(frequency_sample+1);
		GaussianWavelength 	= generator.Alloc1DArray_double(frequency_sample+1);

		for( int f = 0; f <= frequency_sample; f++ ) {
			GaussianFreq[f] 		= f_min + f*df; // => m1*df + f*df => (f_min + f*df)
			GaussianAngularFreq[f]	= 2.0 * PI * GaussianFreq[f];
			GaussianWavelength[f]	= lightspeed / GaussianFreq[f];
		}

		// Temporarily set snapshot point
		Snapshot_x = SIZE_X/2;
		Snapshot_y = SIZE_Y/2;
		Snapshot_z = SIZE_Z/2;

		AllocPhasorForGaussian();
	}

}

void Fourier::AllocPhasorForSine() {
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

void Fourier::AllocPhasorForGaussian() {
	ArrayGenerator generator;

	ex_phasor_G_sin 	= generator.Alloc1DArray_double(frequency_sample+1);
	ex_phasor_G_cos 	= generator.Alloc1DArray_double(frequency_sample+1);
	abs_ex_phasor_G 	= generator.Alloc1DArray_double(frequency_sample+1);
	ex_phase_G			= generator.Alloc1DArray_double(frequency_sample+1);

	hy_phasor_G_sin 	= generator.Alloc1DArray_double(frequency_sample+1);
	hy_phasor_G_cos 	= generator.Alloc1DArray_double(frequency_sample+1);
	abs_hy_phasor_G 	= generator.Alloc1DArray_double(frequency_sample+1);
	hy_phase_G			= generator.Alloc1DArray_double(frequency_sample+1);


	Ex_phasor_G_sin 	= generator.Alloc1DArray_double(frequency_sample+1);
	Ex_phasor_G_cos 	= generator.Alloc1DArray_double(frequency_sample+1);
	abs_Ex_phasor_G 	= generator.Alloc1DArray_double(frequency_sample+1);
	Ex_phase_G			= generator.Alloc1DArray_double(frequency_sample+1);

	Ey_phasor_G_sin 	= generator.Alloc1DArray_double(frequency_sample+1);
	Ey_phasor_G_cos 	= generator.Alloc1DArray_double(frequency_sample+1);
	abs_Ey_phasor_G 	= generator.Alloc1DArray_double(frequency_sample+1);
	Ey_phase_G			= generator.Alloc1DArray_double(frequency_sample+1);

	Ez_phasor_G_sin 	= generator.Alloc1DArray_double(frequency_sample+1);
	Ez_phasor_G_cos 	= generator.Alloc1DArray_double(frequency_sample+1);
	abs_Ez_phasor_G 	= generator.Alloc1DArray_double(frequency_sample+1);
	Ez_phase_G			= generator.Alloc1DArray_double(frequency_sample+1);

	Hx_phasor_G_sin 	= generator.Alloc1DArray_double(frequency_sample+1);
	Hx_phasor_G_cos 	= generator.Alloc1DArray_double(frequency_sample+1);
	abs_Hx_phasor_G 	= generator.Alloc1DArray_double(frequency_sample+1);
	Hx_phase_G			= generator.Alloc1DArray_double(frequency_sample+1);

	Hy_phasor_G_sin 	= generator.Alloc1DArray_double(frequency_sample+1);
	Hy_phasor_G_cos 	= generator.Alloc1DArray_double(frequency_sample+1);
	abs_Hy_phasor_G 	= generator.Alloc1DArray_double(frequency_sample+1);
	Hy_phase_G			= generator.Alloc1DArray_double(frequency_sample+1);

	Hz_phasor_G_sin 	= generator.Alloc1DArray_double(frequency_sample+1);
	Hz_phasor_G_cos 	= generator.Alloc1DArray_double(frequency_sample+1);
	abs_Hz_phasor_G 	= generator.Alloc1DArray_double(frequency_sample+1);
	Hz_phase_G			= generator.Alloc1DArray_double(frequency_sample+1);
}

Fourier::~Fourier() {
	if( SourceMode == 1 ) {
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
	else if( SourceMode == 2 ) {
		delete[] GaussianFreq; GaussianFreq = NULL;
		delete[] GaussianAngularFreq; GaussianAngularFreq = NULL;
		delete[] GaussianWavelength; GaussianWavelength = NULL;
	
		delete[] ex_phasor_G_sin; ex_phasor_G_sin = NULL;
		delete[] ex_phasor_G_cos; ex_phasor_G_cos = NULL;
		delete[] abs_ex_phasor_G; abs_ex_phasor_G = NULL;
		delete[] ex_phase_G; ex_phase_G = NULL;

		delete[] hy_phasor_G_sin; hy_phasor_G_sin = NULL;
		delete[] hy_phasor_G_cos; hy_phasor_G_cos = NULL;
		delete[] abs_hy_phasor_G; abs_hy_phasor_G = NULL;
		delete[] hy_phase_G; hy_phase_G = NULL;

		delete[] Ex_phasor_G_sin; Ex_phasor_G_sin = NULL;
		delete[] Ex_phasor_G_cos; Ex_phasor_G_cos = NULL;
		delete[] abs_Ex_phasor_G; abs_Ex_phasor_G = NULL;
		delete[] Ex_phase_G; Ex_phase_G = NULL;

		delete[] Ey_phasor_G_sin; Ey_phasor_G_sin = NULL;
		delete[] Ey_phasor_G_cos; Ey_phasor_G_cos = NULL;
		delete[] abs_Ey_phasor_G; abs_Ey_phasor_G = NULL;
		delete[] Ey_phase_G; Ey_phase_G = NULL;

		delete[] Ez_phasor_G_sin; Ez_phasor_G_sin = NULL;
		delete[] Ez_phasor_G_cos; Ez_phasor_G_cos = NULL;
		delete[] abs_Ez_phasor_G; abs_Ez_phasor_G = NULL;
		delete[] Ez_phase_G; Ez_phase_G = NULL;

		delete[] Hx_phasor_G_sin; Hx_phasor_G_sin = NULL;
		delete[] Hx_phasor_G_cos; Hx_phasor_G_cos = NULL;
		delete[] abs_Hx_phasor_G; abs_Hx_phasor_G = NULL;
		delete[] Hx_phase_G; Hx_phase_G = NULL;

		delete[] Hy_phasor_G_sin; Hy_phasor_G_sin = NULL;
		delete[] Hy_phasor_G_cos; Hy_phasor_G_cos = NULL;
		delete[] abs_Hy_phasor_G; abs_Hy_phasor_G = NULL;
		delete[] Hy_phase_G; Hy_phase_G = NULL;

		delete[] Hz_phasor_G_sin; Hz_phasor_G_sin = NULL;
		delete[] Hz_phasor_G_cos; Hz_phasor_G_cos = NULL;
		delete[] abs_Hz_phasor_G; abs_Hz_phasor_G = NULL;
		delete[] Hz_phase_G; Hz_phase_G = NULL;

	}
}

void Fourier::FT_SineWave(double ***Ex, double ***Ey, double ***Ez,
						  double ***Hx, double ***Hy, double ***Hz,
						  double *ex,   double *hy,   int t         ) {

	if( SourceMode == 1 ) {
	  if( t > fourier_start && t <= fourier_end ) {

		// 1D fields do FT within the whole space grids.
			/* There's no need to do FT on 1D fields because they are without
			   any TFSF but only with the source.
			   Just focus on 3D fields' Fourier Transformation.
			*/

		// 3D fields do FT within the whole space grids.
		for( int i = 0; i < SIZE_X-1; i++ )
			for( int j = 0; j < SIZE_Y; j++ )
				for( int k = 0; k < SIZE_Z; k++ ) {
					Ex_phasor_sin[i][j][k] += Ex[i][j][k] * sin(angularFreq*dt*t);
					Ex_phasor_cos[i][j][k] += Ex[i][j][k] * cos(angularFreq*dt*t);

					// Modify fields because of the source
					if( (i>=startX && i<=endX) && (j>=startY+1 && j<=endY ) && (k>=startZ && k<=endZ) ) {
						Ex_phasor_sin[i][j][k] -= ex[k] * sin(angularFreq*dt*t);
						Ex_phasor_cos[i][j][k] -= ex[k] * cos(angularFreq*dt*t);
					}
		}
		for( int i = 0; i < SIZE_X; i++ )
			for( int j = 0; j < SIZE_Y-1; j++ )
				for( int k = 0; k < SIZE_Z; k++ ) {
					Ey_phasor_sin[i][j][k] += Ey[i][j][k] * sin(angularFreq*dt*t);
					Ey_phasor_cos[i][j][k] += Ey[i][j][k] * cos(angularFreq*dt*t);
		}
		for( int i = 0; i < SIZE_X; i++ )
			for( int j = 0; j < SIZE_Y; j++ )
				for( int k = 0; k < SIZE_Z-1; k++ ) {
					Ez_phasor_sin[i][j][k] += Ez[i][j][k] * sin(angularFreq*dt*t);
					Ez_phasor_cos[i][j][k] += Ez[i][j][k] * cos(angularFreq*dt*t);
		}
		for( int i = 0; i < SIZE_X; i++ )
			for( int j = 0; j < SIZE_Y-1; j++ )
				for( int k = 0; k < SIZE_Z-1; k++ ) {
					Hx_phasor_sin[i][j][k] += Hx[i][j][k] * sin(angularFreq*dt*t);
					Hx_phasor_cos[i][j][k] += Hx[i][j][k] * cos(angularFreq*dt*t);
		}
		for( int i = 0; i < SIZE_X-1; i++ )
			for( int j = 0; j < SIZE_Y; j++ )
				for( int k = 0; k < SIZE_Z-1; k++ )	{
					Hy_phasor_sin[i][j][k] += Hy[i][j][k] * sin(angularFreq*dt*t);
					Hy_phasor_cos[i][j][k] += Hy[i][j][k] * cos(angularFreq*dt*t);
		
					// Modify fields because of the source
					if( (i>=startX && i<=endX) && (j>=startY+1 && j<=endY) && (k>=startZ && k<=endZ-1) ) {
						Hy_phasor_sin[i][j][k] -= hy[k] * sin(angularFreq*dt*t);
						Hy_phasor_cos[i][j][k] -= hy[k] * cos(angularFreq*dt*t);
					}
		}
		for( int i = 0; i < SIZE_X-1; i++ )
			for( int j = 0; j < SIZE_Y-1; j++ )
				for( int k = 0; k < SIZE_Z; k++ ) {
					Hz_phasor_sin[i][j][k] += Hz[i][j][k] * sin(angularFreq*dt*t);
					Hz_phasor_cos[i][j][k] += Hz[i][j][k] * cos(angularFreq*dt*t);
		}
		    
		/*ex_Re += ex[startZ] * sin(angularFreq*t*dt)*dt;
		ex_Im += ex[startZ] * cos(angularFreq*t*dt)*dt;

		hy_Re += hy[startZ] * cos(angularFreq*t*dt)*dt;
		hy_Im += hy[startZ] * sin(angularFreq*t*dt)*dt;*/

	  }
	}

}

void Fourier::FT_GaussianWave(double ***Ex, double ***Ey, double ***Ez,
							  double ***Hx, double ***Hy, double ***Hz,
							  double *ex,   double *hy,   int t         ) {
	int i, j, k;

	if( SourceMode == 2 ) {

		k = startZ;
		// Do FT on 1D source field at a fixed point
		for( int f = 0; f <= frequency_sample; f++ ) {
			ex_phasor_G_sin[f] += ex[k] * sin(2*PI*(f_min+f*df)*t*dt) * dt;
			ex_phasor_G_cos[f] += ex[k] * cos(2*PI*(f_min+f*df)*t*dt) * dt;

			hy_phasor_G_sin[f] += hy[k] * sin(2*PI*(f_min+f*df)*t*dt) * dt;
			hy_phasor_G_cos[f] += hy[k] * cos(2*PI*(f_min+f*df)*t*dt) * dt;
		}

		i = Snapshot_x;
		j = Snapshot_y;
		k = Snapshot_z;
		// Do FT on 3D fields at a fixed point
		for( int f = 0; f <= frequency_sample; f++ ) {
			Ex_phasor_G_sin[f] += Ex[i][j][k] * sin(2*PI*(f_min+f*df)*t*dt) * dt;
			Ex_phasor_G_cos[f] += Ex[i][j][k] * cos(2*PI*(f_min+f*df)*t*dt) * dt;
		
			Ey_phasor_G_sin[f] += Ey[i][j][k] * sin(2*PI*(f_min+f*df)*t*dt) * dt;
			Ey_phasor_G_cos[f] += Ey[i][j][k] * cos(2*PI*(f_min+f*df)*t*dt) * dt;

			Ez_phasor_G_sin[f] += Ez[i][j][k] * sin(2*PI*(f_min+f*df)*t*dt) * dt;
			Ez_phasor_G_cos[f] += Ez[i][j][k] * cos(2*PI*(f_min+f*df)*t*dt) * dt;

			Hx_phasor_G_sin[f] += Hx[i][j][k] * sin(2*PI*(f_min+f*df)*t*dt) * dt;
			Hx_phasor_G_cos[f] += Hx[i][j][k] * cos(2*PI*(f_min+f*df)*t*dt) * dt;

			Hy_phasor_G_sin[f] += Hy[i][j][k] * sin(2*PI*(f_min+f*df)*t*dt) * dt;
			Hy_phasor_G_cos[f] += Hy[i][j][k] * cos(2*PI*(f_min+f*df)*t*dt) * dt;

			Hz_phasor_G_sin[f] += Hz[i][j][k] * sin(2*PI*(f_min+f*df)*t*dt) * dt;
			Hz_phasor_G_cos[f] += Hz[i][j][k] * cos(2*PI*(f_min+f*df)*t*dt) * dt;
		}


		/*for( int i = 0; i < SIZE_X-1; i++ )
			for( int j = 0; j < SIZE_Y-1; j++ ) {
				R_Ex_Im[i][j][f]=R_Ex_Im[i][j][f]+Ex[i][j][re_z]*sin(2.0*PI*(f_min+f*df)*t*dt) * dt;
				R_Ex_Re[i][j][f]=R_Ex_Re[i][j][f]+Ex[i][j][re_z]*cos(2.0*PI*(f_min+f*df)*t*dt) * dt;

				R_Hy_Im[i][j][f]=R_Hy_Im[i][j][f]+Hy[i][j][re_z]*sin(2.0*PI*(f_min+f*df)*t*dt) * dt;
				R_Hy_Re[i][j][f]=R_Hy_Re[i][j][f]+Hy[i][j][re_z]*cos(2.0*PI*(f_min+f*df)*t*dt) * dt;

				T_Ex_Im[i][j][f] = T_Ex_Im[i][j][f] + Ex[i][j][tr_z]*sin(2.0*PI*(f_min+f*df) *t*dt) * dt;
				T_Ex_Re[i][j][f] = T_Ex_Re[i][j][f] + Ex[i][j][tr_z]*cos(2.0*PI*(f_min+f*df) *t*dt) * dt;

				T_Hy_Im[i][j][f] = T_Hy_Im[i][j][f] + Hy[i][j][tr_z]*sin(2.0*PI*(f_min+f*df) *t*dt) * dt;
				T_Hy_Re[i][j][f] = T_Hy_Re[i][j][f] + Hy[i][j][tr_z]*cos(2.0*PI*(f_min+f*df) *t*dt) * dt;

				R_Ey_Im[i][j][f]=R_Ey_Im[i][j][f]+Ey[i][j][re_z]*sin(2.0*PI*(f_min+f*df) *t*dt) * dt;
				R_Ey_Re[i][j][f]=R_Ey_Re[i][j][f]+Ey[i][j][re_z]*cos(2.0*PI*(f_min+f*df) *t*dt) * dt;

				R_Hx_Im[i][j][f]=R_Hx_Im[i][j][f]+Hx[i][j][re_z]*sin(2.0*PI*(f_min+f*df) *t*dt) * dt;
				R_Hx_Re[i][j][f]=R_Hx_Re[i][j][f]+Hx[i][j][re_z]*cos(2.0*PI*(f_min+f*df) *t*dt) * dt;

				T_Ey_Im[i][j][f] = T_Ey_Im[i][j][f] + Ey[i][j][tr_z]*sin(2.0*PI*(f_min+f*df) *t*dt) * dt;
				T_Ey_Re[i][j][f] = T_Ey_Re[i][j][f] + Ey[i][j][tr_z]*cos(2.0*PI*(f_min+f*df) *t*dt) * dt;

				T_Hx_Im[i][j][f] = T_Hx_Im[i][j][f] + Hx[i][j][tr_z]*sin(2.0*PI*(f_min+f*df) *t*dt) * dt;
				T_Hx_Re[i][j][f] = T_Hx_Re[i][j][f] + Hx[i][j][tr_z]*cos(2.0*PI*(f_min+f*df) *t*dt) * dt;
			}*/

	}
}

void Fourier::Phasor_SineWave() {
	if( SourceMode == 1 ) {
		for( int i = 0; i < SIZE_X-1; i++ )
			for( int j = 0; j < SIZE_Y; j++ )
				for( int k = 0; k < SIZE_Z; k++ ) {
					Ex_phasor_sin[i][j][k] = (2.0/stepPerPeriod) * Ex_phasor_sin[i][j][k];
					Ex_phasor_cos[i][j][k] = (2.0/stepPerPeriod) * Ex_phasor_cos[i][j][k];
					abs_Ex_phasor[i][j][k] = sqrt( (Ex_phasor_sin[i][j][k] * Ex_phasor_sin[i][j][k]) +
												   (Ex_phasor_cos[i][j][k] * Ex_phasor_cos[i][j][k]) );
					Ex_phase[i][j][k] = 180.0/PI*atan2(Ex_phasor_sin[i][j][k],Ex_phasor_cos[i][j][k]);
				}

		for( int i = 0; i < SIZE_X; i++ )
			for( int j = 0; j < SIZE_Y-1; j++ )
				for( int k = 0; k < SIZE_Z; k++ ) {
					Ey_phasor_sin[i][j][k] = (2.0/stepPerPeriod) * Ey_phasor_sin[i][j][k];
					Ey_phasor_cos[i][j][k] = (2.0/stepPerPeriod) * Ey_phasor_cos[i][j][k];
					abs_Ey_phasor[i][j][k] = sqrt( (Ey_phasor_sin[i][j][k] * Ey_phasor_sin[i][j][k]) +
												   (Ey_phasor_cos[i][j][k] * Ey_phasor_cos[i][j][k]) );
					Ey_phase[i][j][k] = 180.0/PI*atan2(Ey_phasor_sin[i][j][k],Ey_phasor_cos[i][j][k]);
				}

		for( int i = 0; i < SIZE_X; i++ )
			for( int j = 0; j < SIZE_Y; j++ )
				for( int k = 0; k < SIZE_Z-1; k++ ) {
					Ez_phasor_sin[i][j][k] = (2.0/stepPerPeriod) * Ez_phasor_sin[i][j][k];
					Ez_phasor_cos[i][j][k] = (2.0/stepPerPeriod) * Ez_phasor_cos[i][j][k];
					abs_Ez_phasor[i][j][k] = sqrt( (Ez_phasor_sin[i][j][k] * Ez_phasor_sin[i][j][k]) +
												   (Ez_phasor_cos[i][j][k] * Ez_phasor_cos[i][j][k]) );
					Ez_phase[i][j][k] = 180.0/PI*atan2(Ez_phasor_sin[i][j][k],Ez_phasor_cos[i][j][k]);
				}

		for( int i = 0; i < SIZE_X; i++ )
			for( int j = 0; j < SIZE_Y-1; j++ )
				for( int k = 0; k < SIZE_Z-1; k++ ) {
					Hx_phasor_sin[i][j][k] = (2.0/stepPerPeriod) * Hx_phasor_sin[i][j][k];
					Hx_phasor_cos[i][j][k] = (2.0/stepPerPeriod) * Hx_phasor_cos[i][j][k];
					abs_Hx_phasor[i][j][k] = sqrt( (Hx_phasor_sin[i][j][k] * Hx_phasor_sin[i][j][k]) +
												   (Hx_phasor_cos[i][j][k] * Hx_phasor_cos[i][j][k]) );
					Hx_phase[i][j][k] = 180.0/PI*atan2(Hx_phasor_sin[i][j][k],Hx_phasor_cos[i][j][k]);
				}

		for( int i = 0; i < SIZE_X-1; i++ )
			for( int j = 0; j < SIZE_Y; j++ )
				for( int k = 0; k < SIZE_Z-1; k++ )	{
					Hy_phasor_sin[i][j][k] = (2.0/stepPerPeriod) * Hy_phasor_sin[i][j][k];
					Hy_phasor_cos[i][j][k] = (2.0/stepPerPeriod) * Hy_phasor_cos[i][j][k];
					abs_Hy_phasor[i][j][k] = sqrt( (Hy_phasor_sin[i][j][k] * Hy_phasor_sin[i][j][k]) +
												   (Hy_phasor_cos[i][j][k] * Hy_phasor_cos[i][j][k]) );
					Hy_phase[i][j][k] = 180.0/PI*atan2(Hy_phasor_sin[i][j][k],Hy_phasor_cos[i][j][k]);
				}

		for( int i = 0; i < SIZE_X-1; i++ )
			for( int j = 0; j < SIZE_Y-1; j++ )
				for( int k = 0; k < SIZE_Z; k++ ) {
					Hz_phasor_sin[i][j][k] = (2.0/stepPerPeriod) * Hz_phasor_sin[i][j][k];
					Hz_phasor_cos[i][j][k] = (2.0/stepPerPeriod) * Hz_phasor_cos[i][j][k];
					abs_Hz_phasor[i][j][k] = sqrt( (Hz_phasor_sin[i][j][k] * Hz_phasor_sin[i][j][k]) +
												   (Hz_phasor_cos[i][j][k] * Hz_phasor_cos[i][j][k]) );
					Hz_phase[i][j][k] = 180.0/PI*atan2(Hz_phasor_sin[i][j][k],Hz_phasor_cos[i][j][k]);
				}
	}
}

void Fourier::Phasor_GaussianWave() {
	if( SourceMode == 2 ) {
		for( int f = 0; f <= frequency_sample; f++ ) {
			abs_ex_phasor_G[f]	= sqrt( (ex_phasor_G_cos[f] * ex_phasor_G_cos[f]) +
										(ex_phasor_G_sin[f] * ex_phasor_G_sin[f]) );
			ex_phase_G[f] = 180/PI*atan2(ex_phasor_G_sin[f],  ex_phasor_G_cos[f]);

			abs_hy_phasor_G[f]	= sqrt( (hy_phasor_G_cos[f] * hy_phasor_G_cos[f]) +
										(hy_phasor_G_sin[f] * hy_phasor_G_sin[f]) );
			hy_phase_G[f] = 180/PI*atan2(hy_phasor_G_sin[f],  hy_phasor_G_cos[f]);

			abs_Ex_phasor_G[f]	= sqrt( (Ex_phasor_G_sin[f] * Ex_phasor_G_sin[f]) +
										(Ex_phasor_G_cos[f] * Ex_phasor_G_cos[f]) );
			Ex_phase_G[f] = 180/PI*atan2(Ex_phasor_G_sin[f],  Ex_phasor_G_cos[f]);

			abs_Ey_phasor_G[f]	= sqrt( (Ey_phasor_G_sin[f] * Ey_phasor_G_sin[f]) +
										(Ey_phasor_G_cos[f] * Ey_phasor_G_cos[f]) );
			Ey_phase_G[f] = 180/PI*atan2(Ey_phasor_G_sin[f],  Ey_phasor_G_cos[f]);

			abs_Ez_phasor_G[f]	= sqrt( (Ez_phasor_G_sin[f] * Ez_phasor_G_sin[f]) +
										(Ez_phasor_G_cos[f] * Ez_phasor_G_cos[f]) );
			Ez_phase_G[f] = 180/PI*atan2(Ez_phasor_G_sin[f],Ez_phasor_G_cos[f]);

			abs_Hx_phasor_G[f]	= sqrt( (Hx_phasor_G_sin[f] * Hx_phasor_G_sin[f]) +
										(Hx_phasor_G_cos[f] * Hx_phasor_G_cos[f]) );
			Hx_phase_G[f] = 180/PI*atan2(Hx_phasor_G_sin[f],  Hx_phasor_G_cos[f]);

			abs_Hy_phasor_G[f]	= sqrt( (Hy_phasor_G_sin[f] * Hy_phasor_G_sin[f]) +
										(Hy_phasor_G_cos[f] * Hy_phasor_G_cos[f]) );
			Hy_phase_G[f] = 180/PI*atan2(Hy_phasor_G_sin[f],  Hy_phasor_G_cos[f]);

			abs_Hz_phasor_G[f]	= sqrt( (Hz_phasor_G_sin[f] * Hz_phasor_G_sin[f]) +
										(Hz_phasor_G_cos[f] * Hz_phasor_G_cos[f]) );
			Hz_phase_G[f] = 180/PI*atan2(Hz_phasor_G_sin[f],  Hz_phasor_G_cos[f]);
		}
	}
}

void Fourier::Output_Phasor_SineWave() {
	// Note: All output data are on x-y plane. If you want to show out the
	//       other slice, just write output codes by your self.
	int k = SIZE_Z/2;
	FILE *file;
	
	if( SourceMode == 1 ) {
		file = fopen("Phasor_Ex.log","w");
		for( int j = 0; j < SIZE_Y; j++ ) {
			for( int i = 0; i < SIZE_X-1; i++ ) {
				fprintf(file, "%g ", abs_Ex_phasor[i][j][k]);
			}
			fprintf(file, "\n");
		}
		fclose(file);

		file = fopen("Phasor_Ey.log","w");
		for( int j = 0; j < SIZE_Y-1; j++ ) {
			for( int i = 0; i < SIZE_X; i++ ) {
				fprintf(file, "%g ", abs_Ey_phasor[i][j][k]);
			}
			fprintf(file, "\n");
		}
		fclose(file);

		file = fopen("Phasor_Ez.log","w");
		for( int j = 0; j < SIZE_Y; j++ ) {
			for( int i = 0; i < SIZE_X; i++ ) {
				fprintf(file, "%g ", abs_Ez_phasor[i][j][k]);
			}
			fprintf(file, "\n");
		}
		fclose(file);

		file = fopen("Phasor_Hx.log","w");
		for( int j = 0; j < SIZE_Y-1; j++ ) {
			for( int i = 0; i < SIZE_X; i++ ) {
				fprintf(file, "%g ", abs_Hx_phasor[i][j][k]);
			}
			fprintf(file, "\n");
		}
		fclose(file);

		file = fopen("Phasor_Hy.log","w");
		for( int j = 0; j < SIZE_Y; j++ ) {
			for( int i = 0; i < SIZE_X-1; i++ ) {
				fprintf(file, "%g ", abs_Hy_phasor[i][j][k]);
			}
			fprintf(file, "\n");
		}
		fclose(file);

		file = fopen("Phasor_Hz.log","w");
		for( int j = 0; j < SIZE_Y-1; j++ ) {
			for( int i = 0; i < SIZE_X-1; i++ ) {
				fprintf(file, "%g ", abs_Hz_phasor[i][j][k]);
			}
			fprintf(file, "\n");
		}
		fclose(file);
	}

	file = NULL;
}

void Fourier::Output_Phase_SineWave() {
	// Note: All output data are on x-y plane.
	int k = SIZE_Z/2;
	FILE *file;

	if( SourceMode == 1 ) {
		file = fopen("Phase_Ex.log","w");
		for( int j = 0; j < SIZE_Y; j++ ) {
			for( int i = 0; i < SIZE_X-1; i++ ) {
				fprintf(file, "%g ", Ex_phase[i][j][k]);
			}
			fprintf(file, "\n");
		}
		fclose(file);

		file = fopen("Phase_Ey.log","w");
		for( int j = 0; j < SIZE_Y-1; j++ ) {
			for( int i = 0; i < SIZE_X; i++ ) {
				fprintf(file, "%g ", Ey_phase[i][j][k]);
			}
			fprintf(file, "\n");
		}
		fclose(file);

		file = fopen("Phase_Ez.log","w");
		for( int j = 0; j < SIZE_Y; j++ ) {
			for( int i = 0; i < SIZE_X; i++ ) {
				fprintf(file, "%g ", Ez_phase[i][j][k]);
			}
			fprintf(file, "\n");
		}
		fclose(file);

		file = fopen("Phase_Hx.log","w");
		for( int j = 0; j < SIZE_Y-1; j++ ) {
			for( int i = 0; i < SIZE_X; i++ ) {
				fprintf(file, "%g ", Hx_phase[i][j][k]);
			}
			fprintf(file, "\n");
		}
		fclose(file);

		file = fopen("Phase_Hy.log","w");
		for( int j = 0; j < SIZE_Y; j++ ) {
			for( int i = 0; i < SIZE_X-1; i++ ) {
				fprintf(file, "%g ", Hy_phase[i][j][k]);
			}
			fprintf(file, "\n");
		}
		fclose(file);

		file = fopen("Phase_Hz.log","w");
		for( int j = 0; j < SIZE_Y-1; j++ ) {
			for( int i = 0; i < SIZE_X-1; i++ ) {
				fprintf(file, "%g ", Hz_phase[i][j][k]);
			}
			fprintf(file, "\n");
		}
		fclose(file);
	}

	file = NULL;
}

void Fourier::OutputFourier() {
	FILE *file;
	file = fopen("fourier.data","w");
	fprintf(file, "----- Fourier Parameter -----\n");
	fprintf(file, "fourier_start = %i\n", fourier_start+1);
	fprintf(file, "fourier_end   = %i\n", fourier_end);
	fclose(file);
	file = NULL;
}