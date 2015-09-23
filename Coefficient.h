#ifndef COEFFICIENT_H
#define COEFFICIENT_H

class Coefficient {
private:
	double c_e;
	double c_h;

	double *Cex;
	double *Chy;

	void InitBasicCoef1D(int size);
	void InitBasicCoef3D(int size_x, int size_y, int size_z);

public:
	Coefficient(int size1D);
	~Coefficient();

	void Init1DCoefWithCpml(int size);
	void OutputCoef(int size1D);

	double *getCex();
	double *getChy();

};

#endif