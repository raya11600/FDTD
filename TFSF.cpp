#include <stdio.h>
#include "TFSF.h"
#include "Parameter.h"
using namespace std;

TFSF::TFSF(int CPMLGrid) {
	Parameter param;
	int SIZE_X = param.SIZE_X;
	int SIZE_Y = param.SIZE_Y;
	int SIZE_Z = param.SIZE_Z;

	TFSFGrid = CPMLGrid + 5;

	startX 	= TFSFGrid - 1;
	endX 	= SIZE_X - TFSFGrid - 1;
	startY 	= TFSFGrid - 1;
	endY 	= SIZE_Y - TFSFGrid - 1;
	startZ 	= TFSFGrid - 1;
	endZ 	= SIZE_Z - TFSFGrid - 1;
}

TFSF::~TFSF() {

}

void TFSF::AddTfsf_XYPlane_E(double ***Ex, double ***Ey, double ***Ez, double *hy) {
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

void TFSF::AddTfsf_XYPlane_H(double ***Hx, double ***Hy, double ***Hz, double *ex) {
	Parameter param;
	int SIZE_X = param.SIZE_X;
	int SIZE_Y = param.SIZE_Y;
	int SIZE_Z = param.SIZE_Z;

	int k = startZ; 
	for( int i = 0; i < SIZE_X-1; i++ )
		for( int j = 0; j < SIZE_Y; j++ ) {
			Hy[i][j][k] += (param.dt/param.dx/param.mu0) * ex[k];
		}
}

void TFSF::AddTfsf_Box_E(double ***Ex, double ***Ey, double ***Ez, double *hy) {
	Parameter param;
	int i, j, k;

	k = startZ;
	for( i = startX; i <= endX; i++ )
		for( j = startY+1; j <= endY; j++ ) {
			Ex[i][j][k] += (param.dt/param.dx/param.eps0) * hy[k];
		}
	k = endZ+1; 
	for( i = startX; i <= endX; i++ )
		for( j = startY+1; j <= endY; j++ ) {
			Ex[i][j][k] -= (param.dt/param.dx/param.eps0) * hy[k-1];
		}

	i = startX;
	for( j = startY+1; j <= endY; j++ )
		for( k = startZ; k <= endZ; k++ ) {
			Ez[i][j][k] -= (param.dt/param.dx/param.eps0) * hy[k];
		}
	i = endX+1;
	for( j = startY+1; j <= endY; j++ )
		for( k = startZ; k <= endZ; k++ ) {
			Ez[i][j][k] += (param.dt/param.dx/param.eps0) * hy[k];
		}
}

void TFSF::AddTfsf_Box_H(double ***Hx, double ***Hy, double ***Hz, double *ex) {
	Parameter param;
	int i, j, k;

	k = startZ; 
	for( i = startX; i <= endX; i++ )
		for( j = startY+1; j <= endY; j++ ) {
			Hy[i][j][k] += (param.dt/param.dx/param.mu0) * ex[k];
		}
	k = endZ;
	for( i = startX; i <= endX; i++ )
		for( j = startY+1; j <= endY; j++ ) {
			Hy[i][j][k] -= (param.dt/param.dx/param.mu0) * ex[k+1];
		}

	j = startY; 
	for( i = startX; i <= endX; i++ )
		for( k = startZ+1; k <= endZ; k++ ) {
			Hz[i][j][k] -= (param.dt/param.dx/param.mu0) * ex[k];
		}
	j = endY;
	for( i = startX; i <= endX; i++ )
		for( k = startZ+1; k <= endZ; k++ ) {
			Hz[i][j][k] += (param.dt/param.dx/param.mu0) * ex[k];
		}
}

int TFSF::getTFSFGrid() {
	return TFSFGrid;
}