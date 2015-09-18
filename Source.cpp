#include <cmath>
#include <iostream>
#include "Source.h"
#include "Parameter.h"
using namespace std;

Source::Source() {
	mode = 1;

	if( mode == 1 ) {
		InitSineWave();
	}
	else if( mode == 2 ) {
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

	lambda 		= 0.85e-6;	//Wave length
	periodTime	= 11;  		//period you run
	double sourceFreq 	= param.lightspeed / lambda;
	double periodTime 	= 1.0 / sourceFreq;           //time in a period
	periodStep  = (int)round( periodTime / param.dt ); //time steps in a period 

	angularFreq = 2.0 * param.PI * sourceFreq;

	totaltime = periodTime * periodStep;
}

void Source::InitGaussianWave() {
	
}

int Source::getmode() {
	return mode;
}

int Source::gettotaltime() {
	return totaltime;
}

int Source::getperiodTime() {
	return periodTime;
}

int Source::getperiodStep() {
	return periodStep;
}

double Source::getangularFreq() {
	return angularFreq;
}