#ifndef FOURIER_H
#define FOURIER_H

#include "TFSF.h"

class Fourier : public TFSF {
protected:
	bool FourierSwitch;
	bool TransAndReflec;

	// Basic Parameters
	int fourier_start;
	int fourier_end;

	double *GaussianFreq;
	double *GaussianAngularFreq;
	double *GaussianWavelength;

	// Temporarily set the snapshot point
	int Snapshot_x;
	int Snapshot_y;
	int Snapshot_z;

private:
	// Phasors for Sine wave
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

	// Phasors for Gaussian wave
	double *ex_phasor_G_sin;
	double *ex_phasor_G_cos;
	double *abs_ex_phasor_G;
	double *ex_phase_G;

	double *hy_phasor_G_sin;
	double *hy_phasor_G_cos;
	double *abs_hy_phasor_G;
	double *hy_phase_G;

	double *Ex_phasor_G_sin;
	double *Ex_phasor_G_cos;
	double *abs_Ex_phasor_G;
	double *Ex_phase_G;

	double *Ey_phasor_G_sin;
	double *Ey_phasor_G_cos;
	double *abs_Ey_phasor_G;
	double *Ey_phase_G;

	double *Ez_phasor_G_sin;
	double *Ez_phasor_G_cos;
	double *abs_Ez_phasor_G;
	double *Ez_phase_G;

	double *Hx_phasor_G_sin;
	double *Hx_phasor_G_cos;
	double *abs_Hx_phasor_G;
	double *Hx_phase_G;

	double *Hy_phasor_G_sin;
	double *Hy_phasor_G_cos;
	double *abs_Hy_phasor_G;
	double *Hy_phase_G;

	double *Hz_phasor_G_sin;
	double *Hz_phasor_G_cos;
	double *abs_Hz_phasor_G;
	double *Hz_phase_G;

	// Variables for Transmittance & Reflectance
	double ex_Re;
	double ex_Im;

	double hy_Re;
	double hy_Im;

	double ***R_Ex_Im;
	double ***R_Ex_Re;
	double ***R_Ey_Im;
	double ***R_Ey_Re;
	double ***R_Hx_Im;
	double ***R_Hx_Re;
	double ***R_Hy_Im;
	double ***R_Hy_Re;

	double ***T_Ex_Im;
	double ***T_Ex_Re;
	double ***T_Ey_Im;
	double ***T_Ey_Re;
	double ***T_Hx_Im;
	double ***T_Hx_Re;
	double ***T_Hy_Im;
	double ***T_Hy_Re;

	double *source_ex_Re;
	double *source_ex_Im;
	double *source_hy_Re;
	double *source_hy_Im;

	double *Poynting_scatter;
	double *Poynting_total;
	double *Poynting_source;

	void AllocPhasorForSine();
	void AllocPhasorForGaussian();

public:
	Fourier();
	~Fourier();

	// Sine wave
	void FT_SineWave(double ***Ex, double ***Ey, double ***Ez,
					 double ***Hx, double ***Hy, double ***Hz,
					 double *ex,   double *hy,   int t         );
	void Phasor_SineWave();
	//void TransReflec_SineWave();
	void Output_Phasor_SineWave();
	void Output_Phase_SineWave();

	// Gaussian wave
	void FT_GaussianWave(double ***Ex, double ***Ey, double ***Ez,
						 double ***Hx, double ***Hy, double ***Hz,
						 double *ex,   double *hy,   int t         );
	void Phasor_GaussianWave();
	void Output_Phasor_GaussianWave();
	void TransReflec_GaussianWave();
	void Output_TandR_GaussianWave();
	
	void OutputFourier();
};

#endif