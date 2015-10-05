#include <cmath>
#include <stdio.h>
#include "Source.h"
using namespace std;

Source::Source() {
	SourceMode = 1;
	// 1: Sine wave
	// 2: Gaussian wave

	if( SourceMode == 1 ) {
		InitSineWave();
	}
	else if( SourceMode == 2 ) {
		InitGaussianWave();
	}
}

Source::~Source() {

}

void Source::InitSineWave() {
	wavelength 		= 0.85e-6;	//unit: m
	sourcePeriod	= 2;
	sourceFreq 		= lightspeed / wavelength;
	timePerPeriod 	= 1.0 / sourceFreq;
	stepPerPeriod  	= (int)round( timePerPeriod / dt );	

	angularFreq 	= 2.0 * PI * sourceFreq;

	totaltime 		= sourcePeriod * stepPerPeriod;
}

void Source::InitGaussianWave() {
	wavelength_max		= 1.1e-6;
	wavelength_min		= 0.7e-6;
	frequency_sample 	= 100; 

	f_max 	= lightspeed / wavelength_min;
	f_min 	= lightspeed / wavelength_max;

	f0		= (f_max+f_min) / 2.0;
	bw		= (f_max-f_min);

	gaussian_width	= (3.0*sqrt(2.0)/sqrt(PI)) * (1.0/bw);

	df 	= bw / frequency_sample;

	total_simulation_time	= 1.0 / df;

	totaltime = (int)round(total_simulation_time / dt);

}

double Source::getSource(int t) {
	if( SourceMode == 1 ) {
		return sin( angularFreq * dt * t );
	}
	else if ( SourceMode == 2 ) {
		int t0 = totaltime / 2;
		return	1.0 / gaussian_width
				* exp(-PI * (t-t0)*dt/gaussian_width * (t-t0)*dt/gaussian_width )
				* sin( 2.0 * PI * f0 * (t-t0) * dt );
	}
}

void Source::outputSettings() {
	FILE *file;
	file = fopen("source.data", "w");
	fprintf(file, "===== Source Data Output =====\n");
	if( SourceMode == 1 ) {
		fprintf(file, "Mode = Sine Wave\n");
	}
	else if( SourceMode == 2 ) {
		fprintf(file, "Mode = Gaussian Wave\n");
	}
	fprintf(file, "Total time steps = %i\n", totaltime);
	fprintf(file, "\n");
	fprintf(file, "\n");
	
	if( SourceMode == 1 ) {
		fprintf(file, "--Sine Wave Detail--\n");
		fprintf(file, "Wavelength = %g m => Frequency = %g\n", wavelength, sourceFreq);
		fprintf(file, "Period number = %i\n", sourcePeriod);
		fprintf(file, "\n");
		fprintf(file, "Time per period = %g\n", timePerPeriod);
		fprintf(file, "Steps per period = %i\n", stepPerPeriod);
		fprintf(file, "\n");
		fprintf(file, "Angular frequency = %g\n", angularFreq);
		fprintf(file, "\n");
		fprintf(file, "\n");
	}
	else if( SourceMode == 2 ) {
		fprintf(file, "--Gaussian Wave Detail--\n");
		fprintf(file, "Sample number = %i\n", frequency_sample);
		fprintf(file, "\n");
		fprintf(file, "Wavelength_max = %g\nWavelength_min = %g\n", wavelength_max, wavelength_min);
		fprintf(file, "\n");
		fprintf(file, "Frequency_max = %g\nFrequency_min = %g\n", f_max, f_min);
		fprintf(file, "\n");
		fprintf(file, "Pitch frequency = %g\n", f0);
		fprintf(file, "Bandwidth in frequency domain = %g\n", bw);
		fprintf(file, "df = %g\n", df);
		fprintf(file, "\n");
		fprintf(file, "Bandwidth in time domain = %g\n", gaussian_width);
		fprintf(file, "Total simulation time = %g\n", total_simulation_time);
		fprintf(file, "\n");
		fprintf(file, "\n");
	}

	fclose(file);
	file = NULL;

}

int Source::getSourceMode() {
	return SourceMode;
}

int Source::gettotaltime() {
	return totaltime;
}
