#include <stdio.h>
#include "Coefficient.h"
#include "ArrayGenerator.h"
#include "Parameter.h"
#include "CPML.h"
using namespace std;

Coefficient::Coefficient(int size1D) {
	Parameter param;
	c_e = -(param.dt/(param.dx*param.eps0));
	c_h = -(param.dt/(param.dx*param.mu0));

	ArrayGenerator generator;
	Cex = generator.Alloc1DArray_double(size1D);
	Chy = generator.Alloc1DArray_double(size1D-1);

	InitBasicCoef1D(size1D);
}

Coefficient::~Coefficient() {
	delete[] Cex; Cex = NULL;
	delete[] Chy; Chy = NULL;
}

void Coefficient::InitBasicCoef1D(int size) {
	// Coefficient for 1D update equation
	for(int i = 0; i < size; i++) { 
		Cex[i] = c_e ;
	}

	for(int i = 0; i < size-1; i++) { 
		Chy[i] = c_h; 
	}
}

void Coefficient::InitBasicCoef3D(int size_x, int size_y, int size_z) {

}

void Coefficient::Init1DCoefWithCpml(int size) {
	CPML cpml;
	int CPMLGrid = cpml.getCPMLGrid();
	double *kappa_e = cpml.getkappa_e();
	double *kappa_h = cpml.getkappa_h();

	// Coefficient for 1D update equation with CPML
	for(int i = 0; i < size; i++) { 
		if ( i >= 1 && i <= 1 + CPMLGrid ) {
			Cex[i] /= kappa_e[CPMLGrid+1-i];
		}
		if ( i >= size-2-CPMLGrid && i <= size-2 ) {
			Cex[i] /= kappa_e[i-(size-2-CPMLGrid)];
		}
	}

	for(int i = 0; i < size-1; i++) { 
		if ( i >= 0 && i <= 0 + CPMLGrid ) {
			Chy[i] /= kappa_h[CPMLGrid-i];
		}
		if ( i >= size-2-CPMLGrid && i <= size-2 ) {
			Chy[i] /= kappa_h[i-(size-2-CPMLGrid)];
		}
	}
}

void Coefficient::OutputCoef(int size1D) {
	FILE *file;
	file = fopen("coefficient.data", "w");
	fprintf(file, "----- Basic parameters -----\n");
	fprintf(file, "c_e = dt/dx/eps0 = %g\n", c_e);
	fprintf(file, "c_h = dt/dx/eps0 = %g\n", c_h);
	fprintf(file, "\n");
	fprintf(file, "----- 1D Cex -----\n");
	for( int i = 0; i < size1D; i++ ) {
		fprintf(file, "%g ", Cex[i]);
	}
	fprintf(file, "\n\n");
	fprintf(file, "----- 1D Chy -----\n");
	for( int i = 0; i < size1D; i++ ) {
		fprintf(file, "%g ", Chy[i]);
	}
	fprintf(file, "\n\n");
	fclose(file);
	file = NULL;
}

double *Coefficient::getCex() {
	return Cex;
}

double *Coefficient::getChy() {
	return Chy;
}