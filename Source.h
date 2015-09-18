#ifndef SOURCE_H
#define SOURCE_H

class Source {
private:
	int		mode;
	int 	totaltime;

	// Sine wave
	double 	lambda;
	int 	periodTime;
	int 	periodStep;
	double 	angularFreq;
	void InitSineWave();

	// Gaussian wave
	void InitGaussianWave();

public:
	Source();
	~Source();

	int 	getmode();
	int 	gettotaltime();
	int 	getperiodTime();
	int 	getperiodStep();
	double 	getangularFreq();

};

#endif