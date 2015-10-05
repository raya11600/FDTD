#ifndef SOURCE_H
#define SOURCE_H

#include "Parameter.h"

class Source : public Parameter {
protected:
	int		SourceMode;
	int 	totaltime;

	// Sine wave
	double	wavelength;			// Wave length
	double	sourceFreq;			// Source frequency
	int 	sourcePeriod;		// Period you run in time domain
	double	timePerPeriod;		// Time in a period
	int 	stepPerPeriod;		// Time steps in a period 
	double	angularFreq;

	// Gaussian wave
	int 	frequency_sample; 	// Sample numbers in frequency domain
	double	wavelength_max;		// Maximum wavelength
	double	wavelength_min;		// Minimum wavelength
	double	f_max;				// Maximum frequency
	double	f_min;				// Minimum frequency
	double	f0;					// Mid of frequency, the pitch frequency
	double	bw;					// Bandwidth of frequency
	double	df;					// Width of df in freq domain
	double	gaussian_width;			// Gaussian pulse width in time domain
	double	total_simulation_time;	// Total time to simulate a Guassian pulse

private:
	void InitSineWave();
	void InitGaussianWave();

public:
	Source();
	~Source();

	double 	getSource(int time);
	void 	outputSettings();

	int 	getSourceMode();
	int 	gettotaltime();
};

#endif