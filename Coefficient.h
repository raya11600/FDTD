#ifndef COEFFICIENT_H
#define COEFFICIENT_H

class Coefficient {
private:
	double c_e;
	double c_h;

	double *Cex;
	double *Chy;

	void InitBasicCoef1D(int SIZE1D);
	void InitBasicCoef3D(int size_x, int size_y, int size_z);

public:
	Coefficient();
	~Coefficient();

	void Init1DCoefWithCpml();
	void OutputCoef();

	double *getCex();
	double *getChy();

};

#endif