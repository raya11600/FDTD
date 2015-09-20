#include <stdio.h>
#include <cmath>
#include "CPML.h"
#include "ArrayGenerator.h"
#include "Parameter.h"
using namespace std;

CPML::CPML() {
	CPMLGrid = 20;

	ArrayGenerator generator;
	B_e = generator.Alloc1DArray_double(CPMLGrid+1);
	B_h = generator.Alloc1DArray_double(CPMLGrid+1);
	C_e = generator.Alloc1DArray_double(CPMLGrid+1);
	C_h = generator.Alloc1DArray_double(CPMLGrid+1);
	kappa_e = generator.Alloc1DArray_double(CPMLGrid+1);
	kappa_h = generator.Alloc1DArray_double(CPMLGrid+1);

	InitCPML();

}

CPML::~CPML() {
	delete[] B_e; B_e = NULL;
	delete[] B_h; B_h = NULL;
	delete[] C_e; C_e = NULL;
	delete[] C_h; C_h = NULL;
	delete[] kappa_e; kappa_e = NULL;
	delete[] kappa_h; kappa_h = NULL;
}

void CPML::InitCPML() {
	Parameter param;

	int m=4; //powerlaw; 3<=m<=4
	int kappa_max=15;
	int ma = 1;
	double sigma_max= 0.8*(m+1)/(param.imp0*param.dx);
	double alpha_max=0.24;

	ArrayGenerator generator;
	double *sigma_e = generator.Alloc1DArray_double(CPMLGrid+1);
	double *sigma_h = generator.Alloc1DArray_double(CPMLGrid+1);
	double *alpha_e = generator.Alloc1DArray_double(CPMLGrid+1);
	double *alpha_h = generator.Alloc1DArray_double(CPMLGrid+1);

	for(int i = 0; i <= CPMLGrid; i++) { 
		sigma_e[i] = sigma_max * pow( (double(i+0.5)/CPMLGrid) , m);
		sigma_h[i] = sigma_max * pow( (double(i+1.0)/CPMLGrid) , m);

		kappa_e[i] = 1 + (kappa_max-1) * pow( (double(i+0.5)/CPMLGrid) , m);
		kappa_h[i] = 1 + (kappa_max-1) * pow( (double(i+1.0)/CPMLGrid) , m);

		alpha_e[i] = alpha_max * pow( (double(CPMLGrid-(i+0.0))/CPMLGrid) , ma);
		alpha_h[i] = alpha_max * pow( (double(CPMLGrid-(i+0.5))/CPMLGrid) , ma);

		B_e[i] = exp( -(param.dt/param.eps0) * (sigma_e[i]/kappa_e[i] + alpha_e[i]) );
		B_h[i] = exp( -(param.dt/param.eps0) * (sigma_h[i]/kappa_h[i] + alpha_h[i]) );

		C_e[i] = sigma_e[i] / kappa_e[i] / (sigma_e[i] + kappa_e[i]*alpha_e[i])
		         * (B_e[i] - 1.0);
		C_h[i] = sigma_h[i] / kappa_h[i] / (sigma_h[i] + kappa_h[i]*alpha_h[i])
		         * (B_h[i] - 1.0);
	}

	delete[] sigma_e; sigma_e = NULL;
	delete[] sigma_h; sigma_h = NULL;
	delete[] alpha_e; alpha_e = NULL;
	delete[] alpha_h; alpha_h = NULL;

}

int CPML::getCPMLGrid() {
	return CPMLGrid;
}

double *CPML::getkappa_e() {
	return kappa_e;
}

double *CPML::getkappa_h() {
	return kappa_h;
}

double *CPML::getB_e() {
	return B_e;
}

double *CPML::getB_h() {
	return B_h;
}

double *CPML::getC_e() {
	return C_e;
}

double *CPML::getC_h() {
	return C_h;
}