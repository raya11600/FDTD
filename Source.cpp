#include <cmath>
#include <stdio.h>
#include <iostream>
#include "Source.h"
#include "Parameter.h"
using namespace std;

Source::Source() {
	SourceMode = 1;
	startGrid = 0;

	if( SourceMode == 1 ) {
		InitSineWave();
	}
	else if( SourceMode == 2 ) {
		InitGaussianWave();
	}
	else {
		cout << "[Error] Parameter.SourceMode error." << endl;
	}
}

Source::~Source() {

}

void Source::InitSineWave() {
	Parameter param;

	wavelength 		= 0.85e-6;	//unit: m
	sourcePeriod	= 11;
	sourceFreq 		= param.lightspeed / wavelength;
	timePerPeriod 	= 1.0 / sourceFreq;
	stepPerPeriod  	= (int)round( timePerPeriod / param.dt );	

	angularFreq 	= 2.0 * param.PI * sourceFreq;

	totaltime 		= sourcePeriod * stepPerPeriod;
}

void Source::InitGaussianWave() {
	Parameter param;

	wavelength_max		= 1.1e-6;
	wavelength_min		= 0.7e-6;
	frequency_sample 	= 201; 

	f_max 	= param.lightspeed / wavelength_min;
	f_min 	= param.lightspeed / wavelength_max;

	f0		= (f_max+f_min) / 2.0;
	bw		= (f_max-f_min);

	gaussian_width	= (3.0*sqrt(2.0)/sqrt(param.PI)) * (1.0/bw);

	df 	= bw / (frequency_sample-1);

	total_simulation_time	= 1.0 / df;

	totaltime = (int)round(total_simulation_time / param.dt);

}

double Source::getSource(int t) {
	Parameter param;

	if( SourceMode == 1 ) {
		return sin( angularFreq * param.dt * t );
	}
	else if ( SourceMode == 2 ) {
		int t0=totaltime/2;
		return	1.0 / gaussian_width
				* exp(-param.PI * (t-t0)*param.dt/gaussian_width * (t-t0)*param.dt/gaussian_width )
				* sin( 2.0 * param.PI * f0 * (t-t0) * param.dt );
	}
	else {
		return -1; // Error code
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
	fprintf(file, "Grid to start = %i\n", startGrid);
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

int Source::getstartGrid() {
	return startGrid;
}

//double Source::getwavelength();
//double Source::getsourceFreq();

int  Source::getsourcePeriod() {
	return sourcePeriod;
}

//double Source::gettimePerPeriod();

int Source::getstepPerPeriod() {
	return stepPerPeriod;
}

//double Source::getangularFreq();