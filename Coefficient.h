#ifndef COEFFICIENT_H
#define COEFFICIENT_H

#include "CPML.h"

class Coefficient : public CPML {
protected:
	// Basic parameter
	double c_e;		// = dt/dx/eps0
	double c_h;		// = dt/dx/mu0

	// 1D Coefficients
	double *Cex;
	double *Chy;

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

private:
	void InitBasicCoef1D();
	void Alloc3DArray();
	void InitBasicCoef3D();

public:
	Coefficient();
	~Coefficient();

	void InitCpmlCoef1D();
	void InitCPMLCoef3D_X();
	void InitCPMLCoef3D_Y();
	void InitCPMLCoef3D_Z();
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