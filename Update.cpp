#include <stdio.h>
#include <iostream>
#include <cmath>
#include "Update.h"
#include "ArrayGenerator.h"
#include "Parameter.h"
#include "CPML.h"
#include "Source.h"
using namespace std;

Update::Update() {
	Parameter param;
	ArrayGenerator generator;

	ex = generator.Alloc1DArray_double(param.SIZE1D);
	hy = generator.Alloc1DArray_double(param.SIZE1D-1);

	ex_now = generator.Alloc1DArray_double(param.SIZE1D);
	ex_bef = generator.Alloc1DArray_double(param.SIZE1D);

	psi_ex = generator.Alloc1DArray_double(param.SIZE1D);
	psi_hy = generator.Alloc1DArray_double(param.SIZE1D-1);

}

Update::~Update() {
	delete[] ex; ex = NULL;
	delete[] hy; hy = NULL;

	delete[] ex_now; ex_now = NULL;
	delete[] ex_bef; ex_bef = NULL;

	delete[] psi_ex; psi_ex = NULL;
	delete[] psi_hy; psi_hy = NULL;

}

void Update::Update1Dfield_e(double *Cex, int t) {
	Parameter param;
	int SIZE1D = param.SIZE1D;

	// Update e field
	for (int k = 1; k < SIZE1D-1; k++) {
		ex_now[k] = ex[k] + Cex[k] * ( hy[k] - hy[k-1] );
	}
	
	// Add Source
	Source source;
	ex_now[SIZE1D/2] = source.getSource(t);

	//if ( t == 1 ) {
	//	ex_now[50] = 1;
	//}

	ex_now[0]=ex_bef[1];
	ex_now[SIZE1D-1]=ex_bef[SIZE1D-2];

	for(int k = 0; k < SIZE1D; k++)
	{ ex_bef[k] = ex[k];
	ex[k] = ex_now[k]; }

}

void Update::Update1Dfield_h(double *Chy, int t) {
	Parameter param;
	int SIZE1D = param.SIZE1D;

	for (int k = 0; k < SIZE1D-1; k++) {
		hy[k] = hy[k] + Chy[k] * (ex[k+1] - ex[k]);
	}
}

void Update::Update1DCpml_ex() {
	Parameter param;
	int SIZE1D = param.SIZE1D;

	CPML cpml;
	int CPMLGrid = cpml.getCPMLGrid();
	double *B_e = cpml.getB_e();
	double *C_e = cpml.getC_e();

	for( int k = 0; k < SIZE1D; k++ ) {
		if( k >= 1 && k <= 1+CPMLGrid ) {
			psi_ex[k] = B_e[CPMLGrid+1-k] * psi_ex[k] + 
						C_e[CPMLGrid+1-k] * (hy[k] - hy[k-1]) / param.dx; 
			ex[k] = ex[k] - (param.dt/param.eps0) * psi_ex[k];
		}
		if( k >= SIZE1D-2-CPMLGrid && k <= SIZE1D-2 ) {
			psi_ex[k] = B_e[k-(SIZE1D-2-CPMLGrid)] * psi_ex[k] +
						C_e[k-(SIZE1D-2-CPMLGrid)] * (hy[k] - hy[k-1]) / param.dx;
			ex[k] = ex[k] - (param.dt/param.eps0) * psi_ex[k];
		}
	}

}

void Update::Update1DCpml_hy() {
	Parameter param;
	int SIZE1D = param.SIZE1D;

	CPML cpml;
	int CPMLGrid = cpml.getCPMLGrid();
	double *B_h = cpml.getB_h();
	double *C_h = cpml.getC_h();

	for( int k = 0; k < SIZE1D-1; k++ ) {
		if( k >= 0 && k <= 0+CPMLGrid ) {
			psi_hy[k] = B_h[CPMLGrid-k] * psi_hy[k] +
						C_h[CPMLGrid-k] * (ex[k+1] - ex[k]) / param.dx;
			hy[k] = hy[k] - (param.dt/param.mu0) * psi_hy[k];
		}
		if( k >= SIZE1D-2-CPMLGrid && k <= SIZE1D-2 ) {
			psi_hy[k] = B_h[k-(SIZE1D-2-CPMLGrid)] * psi_hy[k] +
						C_h[k-(SIZE1D-2-CPMLGrid)] * (ex[k+1] - ex[k]) / param.dx;
			hy[k] = hy[k] - (param.dt/param.mu0) * psi_hy[k];
		}
	}

}

double *Update::getex() {
	return ex;
}

double *Update::gethy() {
	return hy;
}