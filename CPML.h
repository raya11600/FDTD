#ifndef CPML_H
#define CPML_H

#include "Parameter.h"

class CPML : public Parameter {
protected:
	bool 	CPMLSwtich;
	int 	CPMLGrid;

	double *B_e;
	double *B_h;
	double *C_e;
	double *C_h;
	double *kappa_e;
	double *kappa_h;

private:
	void InitCPML();

public:
	CPML();
	~CPML();

	void OutputCPML();

	int getCPMLGrid();
	double *getB_e();
	double *getB_h();
	double *getC_e();
	double *getC_h();
	double *getkappa_e();
	double *getkappa_h();

};


#endif