#ifndef SOURCE_H
#define SOURCE_H

class Source {
private:
	int		SourceMode;
	int 	totaltime;

	int 	startGrid;

	// Sine wave
	double	wavelength;			// Wave length
	double	sourceFreq;			// Source frequency
	int 	sourcePeriod;		// Period you run in time domain
	double	timePerPeriod;		// Time in a period
	int 	stepPerPeriod;		// Time steps in a period 
	double	angularFreq;
	void InitSineWave();

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

	void InitGaussianWave();

public:
	Source();
	~Source();

	int 	getSourceMode();
	int 	gettotaltime();
	int 	getstartGrid();

	double 	getSource(int time);
	void 	outputSettings();

};

#endif