#ifndef COEFFICIENT_H
#define COEFFICIENT_H

class Coefficient {
private:
	// Basic parameter
	double c_e;		// = dt/dx/eps0
	double c_h;		// = dt/dx/mu0

	// 1D Coefficients
	double *Cex;
	double *Chy;

	void InitBasicCoef1D(int SIZE1D);

	// 3D Coefficients
	double ***Cexz;
	double ***Cexy;
	double ***Ceyx;
	double ***Ceyz;
	double ***Cezy;
	double ***Cezx;

	double ***Chxz;
	double ***Chxy;
	double ***Chyx;
	double ***Chyz;
	double ***Chzy;
	double ***Chzx;

	void InitBasicCoef3D(int size_x, int size_y, int size_z);

public:
	Coefficient();
	~Coefficient();

	void Init1DCoefWithCpml();
	void OutputCoef();

	double *getCex();
	double *getChy();

	double ***getCexz();
	double ***getCexy();
	double ***getCeyx();
	double ***getCeyz();
	double ***getCezy();
	double ***getCezx();

	double ***getChxz();
	double ***getChxy();
	double ***getChyx();
	double ***getChyz();
	double ***getChzy();
	double ***getChzx();

};

#endif