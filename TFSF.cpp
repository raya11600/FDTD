#include <stdio.h>
#include "TFSF.h"
#include "Parameter.h"
using namespace std;

TFSF::TFSF(int CPMLGrid) {

	TFSFGrid = CPMLGrid + 5;

	startZ = TFSF - 1;
}

TFSF::~TFSF() {

}

void TFSF::AddTfsf2Sides_E(double ***Ex, double ***Ey, double ***Ez, double *hy) {
	Parameter param;
	int SIZE_X = param.SIZE_X;
	int SIZE_Y = param.SIZE_Y;
	int SIZE_Z = param.SIZE_Z;

	int k = startZ;
	for( int i = 0; i < SIZE_X-1; i++ )
		for( int j = 1; j < SIZE_Y-1; j++ ) { 
			Ex[i][j][k] += (param.dt/param.dx/param.eps0) * hy[k];
		}

}

void TFSF::AddTfsf2Sides_H(double ***Hx, double ***Hy, double ***Hz, double *ex) {
	Parameter param;
	int SIZE_X = param.SIZE_X;
	int SIZE_Y = param.SIZE_Y;
	int SIZE_Z = param.SIZE_Z;

	k=startZ; 
	for( int i = 0; i < SIZE_X-1; i++ )
		for( int j = 0; j < SIZE_Y; j++ ) {
		  	Hy[i][j][k] += (param.dt/param.dx/param.mu0) * ex[k];
		}
}

void TFSF::AddTfsf6Sides_E() {

}

void TFSF::AddTfsf6Sides_H() {

}

int TFSF::getTFSFGrid() {
	return TFSFGrid;
}