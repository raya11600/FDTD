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

	Alloc3DArray(param.SIZE_X, param.SIZE_Y, param.SIZE_Z);

	InitBasicCoef1D(param.SIZE1D);
	InitBasicCoef3D(param.SIZE_X, param.SIZE_Y, param.SIZE_Z);
}

void Coefficient::Alloc3DArray(int SIZE_X, int SIZE_Y, int SIZE_Z) {
	ArrayGenerator generator;

	Cexz = generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y, SIZE_Z);
	Cexy = generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y, SIZE_Z);
	Ceyx = generator.Alloc3DArray_double(SIZE_X, SIZE_Y-1, SIZE_Z);
	Ceyz = generator.Alloc3DArray_double(SIZE_X, SIZE_Y-1, SIZE_Z);
	Cezy = generator.Alloc3DArray_double(SIZE_X, SIZE_Y, SIZE_Z-1);
	Cezx = generator.Alloc3DArray_double(SIZE_X, SIZE_Y, SIZE_Z-1);

	Chxz = generator.Alloc3DArray_double(SIZE_X, SIZE_Y-1, SIZE_Z-1);
	Chxy = generator.Alloc3DArray_double(SIZE_X, SIZE_Y-1, SIZE_Z-1);
	Chyx = generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y, SIZE_Z-1);
	Chyz = generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y, SIZE_Z-1);
	Chzy = generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y-1, SIZE_Z);
	Chzx = generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y-1, SIZE_Z);
}

Coefficient::~Coefficient() {
	delete[] Cex; Cex = NULL;
	delete[] Chy; Chy = NULL;

	Parameter param;
	int SIZE_X = param.SIZE_X;
	int SIZE_Y = param.SIZE_Y;

	for( int i = 0; i < SIZE_X; i++ ) {
		for( int j = 0; j < SIZE_Y; j++ ) {
			if( i != SIZE_X-1 ) { 
				delete[] Cexz[i][j];
				delete[] Cexy[i][j];
				delete[] Chyx[i][j];
				delete[] Chyz[i][j];
			}
			if( j != SIZE_Y-1 ) {
				delete[] Ceyx[i][j];
				delete[] Ceyz[i][j];
				delete[] Chxz[i][j];
				delete[] Chxy[i][j];
			}
			delete[] Cezy[i][j];
			delete[] Cezx[i][j];
			if( i != SIZE_X-1 && j != SIZE_Y-1 ) {
				delete[] Chzy[i][j];
				delete[] Chzx[i][j];
			}
		}
		if( i != SIZE_X-1 ) {
			delete[] Cexz[i];
			delete[] Cexy[i];
			delete[] Chyx[i];
			delete[] Chyz[i];
			delete[] Chzy[i];
			delete[] Chzx[i];
		}
		delete[] Ceyx[i];
		delete[] Ceyz[i];
		delete[] Cezy[i];
		delete[] Cezx[i];
		delete[] Chxz[i];
		delete[] Chxy[i];

	}
	delete[] Cexz; Cexz = NULL;
	delete[] Cexy; Cexy = NULL;
	delete[] Ceyx; Ceyx = NULL;
	delete[] Ceyz; Ceyz = NULL;
	delete[] Cezy; Cezy = NULL;
	delete[] Cezx; Cezx = NULL;
	delete[] Chxz; Chxz = NULL;
	delete[] Chxy; Chxy = NULL;
	delete[] Chyx; Chyx = NULL;
	delete[] Chyz; Chyz = NULL;
	delete[] Chzy; Chzy = NULL;
	delete[] Chzx; Chzx = NULL;
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

double ***Coefficient::getCexz() {
	return Cexz;
}

double ***Coefficient::getCexy() {
	return Cexy;
}

double ***Coefficient::getCeyx() {
	return Ceyx;
}

double ***Coefficient::getCeyz() {
	return Ceyz;
}

double ***Coefficient::getCezy() {
	return Cezy;
}

double ***Coefficient::getCezx() {
	return Cezx;
}

double ***Coefficient::getChxz() {
	return Chxz;
}

double ***Coefficient::getChxy() {
	return Chxy;
}

double ***Coefficient::getChyx() {
	return Chyx;
}

double ***Coefficient::getChyz() {
	return Chyz;
}

double ***Coefficient::getChzy() {
	return Chzy;
}

double ***Coefficient::getChzx() {
	return Chzx;
}
