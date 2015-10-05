#ifndef FOURIER_H
#define FOURIER_H

#include "TFSF.h"

class Fourier : public TFSF {
protected:
	// Basic Parameters
	int fourier_start;
	int fourier_end;

	double *GaussianFreq;
	double *GaussianAngularFreq;
	double *GaussianWavelength;

private:
	// 1D Phasors
	double ex_Re;
	double ex_Im;

	double hy_Re;
	double hy_Im;

	// 3D Phasors
	double ***Ex_phasor_sin;
	double ***Ex_phasor_cos;
	double ***abs_Ex_phasor;
	double ***Ex_phase;

	double ***Ey_phasor_sin;
	double ***Ey_phasor_cos;
	double ***abs_Ey_phasor;
	double ***Ey_phase;

	double ***Ez_phasor_sin;
	double ***Ez_phasor_cos;
	double ***abs_Ez_phasor;
	double ***Ez_phase;

	double ***Hx_phasor_sin;
	double ***Hx_phasor_cos;
	double ***abs_Hx_phasor;
	double ***Hx_phase;

	double ***Hy_phasor_sin;
	double ***Hy_phasor_cos;
	double ***abs_Hy_phasor;
	double ***Hy_phase;

	double ***Hz_phasor_sin;
	double ***Hz_phasor_cos;
	double ***abs_Hz_phasor;
	double ***Hz_phase;

	void Alloc3DArray();

public:
	Fourier();
	~Fourier();

	void FT_SineWave(double ***Ex, double ***Ey, double ***Ez,
					 double ***Hx, double ***Hy, double ***Hz,
					 double *ex,   double *hy,   int t         );
	void FT_GaussianWave();

	void Phasor_SineWave();

	void Output_Phasor_SineWave();
	void Output_Phase_SineWave();
};

#endif