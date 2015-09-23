#include <stdio.h>
#include "Coefficient.h"
#include "ArrayGenerator.h"
#include "Parameter.h"
#include "CPML.h"
using namespace std;

Coefficient::Coefficient() {
	Parameter param;

	c_e = param.dt/(param.dx*param.eps0);
	c_h = param.dt/(param.dx*param.mu0);

	ArrayGenerator generator;
	Cex = generator.Alloc1DArray_double(param.SIZE1D);
	Chy = generator.Alloc1DArray_double(param.SIZE1D-1);

	InitBasicCoef1D(param.SIZE1D);
	InitBasicCoef3D(param.SIZE_X, param.SIZE_Y, param.SIZE_Z);
}

Coefficient::~Coefficient() {
	delete[] Cex; Cex = NULL;
	delete[] Chy; Chy = NULL;
}

void Coefficient::InitBasicCoef1D(int SIZE1D) {
	// Coefficient for 1D update equation
	for(int i = 0; i < SIZE1D; i++) { 
		Cex[i] = c_e;
	}

	for(int i = 0; i < SIZE1D-1; i++) { 
		Chy[i] = c_h;
	}
}

void Coefficient::InitBasicCoef3D(int SIZE_X, int SIZE_Y, int SIZE_Z) {
	for( int i = 0; i < SIZE_X-1; i++ )
		for( int j = 1; j < SIZE_Y-1; j++ )
			for( int k = 1; k < SIZE_Z-1;k++) {
				Cexz[i][j][k] = c_e;
				Cexy[i][j][k] = c_e;
			}

	for( int i = 1; i < SIZE_X-1; i++ )
		for( int j = 0; j < SIZE_Y-1; j++ )
			for( int k = 1; k < SIZE_Z-1; k++ ) {
				Ceyx[i][j][k] = c_e;
				Ceyz[i][j][k] = c_e;
			}

	for( int i = 1; i < SIZE_X-1; i++ )
		for( int j = 1; j < SIZE_Y-1; j++ )
			for( int k = 0; k < SIZE_Z-1; k++ ) {
				Cezy[i][j][k] = c_e;
				Cezx[i][j][k] = c_e;
			}

	for( int i = 0; i < SIZE_X; i++ )
		for( int j = 0; j < SIZE_Y-1; j++ )
			for( int k = 0; k < SIZE_Z-1; k++ ) {
				Chxz[i][j][k] = c_h;
				Chxy[i][j][k] = c_h;
			}

	for( int i = 0; i < SIZE_X-1; i++ )
		for( int j = 0; j < SIZE_Y; j++ )
			for( int k = 0; k <SIZE_Z-1; k++ ) {
				Chyx[i][j][k] = c_h;
				Chyz[i][j][k] = c_h;
			}

	for( int i = 0; i < SIZE_X-1; i++ )
		for( int j = 0; j < SIZE_Y-1; j++ )
			for( int k = 0; k < SIZE_Z; k++ ) {
				Chzy[i][j][k] = c_h;
				Chzx[i][j][k] = c_h;
			}
}

void Coefficient::Init1DCoefWithCpml() {
	Parameter param;
	int SIZE1D = param.SIZE1D;

	CPML cpml;
	int CPMLGrid = cpml.getCPMLGrid();
	double *kappa_e = cpml.getkappa_e();
	double *kappa_h = cpml.getkappa_h();

	// Coefficient for 1D update equation with CPML
	for(int i = 0; i < SIZE1D; i++) { 
		if ( i >= 1 && i <= 1 + CPMLGrid ) {
			Cex[i] /= kappa_e[CPMLGrid+1-i];
		}
		if ( i >= SIZE1D-2-CPMLGrid && i <= SIZE1D-2 ) {
			Cex[i] /= kappa_e[i-(SIZE1D-2-CPMLGrid)];
		}
	}

	for(int i = 0; i < SIZE1D-1; i++) { 
		if ( i >= 0 && i <= 0 + CPMLGrid ) {
			Chy[i] /= kappa_h[CPMLGrid-i];
		}
		if ( i >= SIZE1D-2-CPMLGrid && i <= SIZE1D-2 ) {
			Chy[i] /= kappa_h[i-(SIZE1D-2-CPMLGrid)];
		}
	}
}

void Coefficient::OutputCoef() {
	Parameter param;
	int SIZE1D = param.SIZE1D;

	FILE *file;
	file = fopen("coefficient.data", "w");
	fprintf(file, "----- Basic parameters -----\n");
	fprintf(file, "c_e = dt/dx/eps0 = %g\n", c_e);
	fprintf(file, "c_h = dt/dx/eps0 = %g\n", c_h);
	fprintf(file, "\n");
	fprintf(file, "----- 1D Cex -----\n");
	for( int i = 0; i < SIZE1D; i++ ) {
		fprintf(file, "%g ", Cex[i]);
	}
	fprintf(file, "\n\n");
	fprintf(file, "----- 1D Chy -----\n");
	for( int i = 0; i < SIZE1D; i++ ) {
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