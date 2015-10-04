#ifndef COEFFICIENT_H
#define COEFFICIENT_H

#include "CPML.h"

class Coefficient {
protected:
	// Basic parameter
	double c_e;		// = dt/dx/eps0
	double c_h;		// = dt/dx/mu0

private:
	// 1D Coefficients
	double *Cex;
	double *Chy;

	void InitBasicCoef1D();

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

	void Alloc3DArray();
	void InitBasicCoef3D();

public:
	Coefficient();
	~Coefficient();

	void Init1DCoefWithCpml();
	void Init3DCoefWithCpml();
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