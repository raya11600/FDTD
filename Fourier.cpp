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
	
		Alloc3DArray();
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

	}

}

void Fourier::Alloc3DArray() {
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
	}
}

void Fourier::FT_SineWave(double ***Ex, double ***Ey, double ***Ez,
						  double ***Hx, double ***Hy, double ***Hz,
						  double *ex,   double *hy,   int t         ) {

	if( SourceMode == 1 ) {
	  if( t > fourier_start && t <= fourier_end ) {

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
		    
		ex_Re += ex[startZ] * sin(angularFreq*t*dt)*dt;
		ex_Im += ex[startZ] * cos(angularFreq*t*dt)*dt;

		hy_Re += hy[startZ] * cos(angularFreq*t*dt)*dt;
		hy_Im += hy[startZ] * sin(angularFreq*t*dt)*dt;

	  }
	}

}

void Fourier::FT_GaussianWave() {
	if( SourceMode == 2 ) {

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

void Fourier::Output_Phasor_SineWave() {
	// Note: All output data are on x-y plane.
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