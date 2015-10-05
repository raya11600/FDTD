#include <stdio.h>
#include "TFSF.h"
using namespace std;

TFSF::TFSF(CPML *cpml) {
	int CPMLGrid = cpml->getCPMLGrid();
	int CPMLMode = cpml->getCPMLMode();

	TFSFSwitch = true;
	// true:  on
	// false: off

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

void TFSF::Add1DSource(double *ex, int t) {
	ex[startZ] = getSource(t);
}

void TFSF::AddTfsf_XYPlane_E(double ***Ex, double ***Ey, double ***Ez, double *hy) {
	int k = startZ;
	for( int i = 0; i < SIZE_X-1; i++ )
		for( int j = 1; j < SIZE_Y-1; j++ ) { 
			Ex[i][j][k] += (dt/dx/eps0) * hy[k];
		}

}

void TFSF::AddTfsf_XYPlane_H(double ***Hx, double ***Hy, double ***Hz, double *ex) {
	int k = startZ; 
	for( int i = 0; i < SIZE_X-1; i++ )
		for( int j = 0; j < SIZE_Y; j++ ) {
			Hy[i][j][k] += (dt/dx/mu0) * ex[k];
		}
}

void TFSF::AddTfsf_Box_E(double ***Ex, double ***Ey, double ***Ez, double *hy) {
	int i, j, k;

	k = startZ;
	for( i = startX; i <= endX; i++ )
		for( j = startY+1; j <= endY; j++ ) {
			Ex[i][j][k] += (dt/dx/eps0) * hy[k];
		}
	k = endZ+1; 
	for( i = startX; i <= endX; i++ )
		for( j = startY+1; j <= endY; j++ ) {
			Ex[i][j][k] -= (dt/dx/eps0) * hy[k-1];
		}

	i = startX;
	for( j = startY+1; j <= endY; j++ )
		for( k = startZ; k <= endZ; k++ ) {
			Ez[i][j][k] -= (dt/dx/eps0) * hy[k];
		}
	i = endX+1;
	for( j = startY+1; j <= endY; j++ )
		for( k = startZ; k <= endZ; k++ ) {
			Ez[i][j][k] += (dt/dx/eps0) * hy[k];
		}
}

void TFSF::AddTfsf_Box_H(double ***Hx, double ***Hy, double ***Hz, double *ex) {
	int i, j, k;

	k = startZ; 
	for( i = startX; i <= endX; i++ )
		for( j = startY+1; j <= endY; j++ ) {
			Hy[i][j][k] += (dt/dx/mu0) * ex[k];
		}
	k = endZ;
	for( i = startX; i <= endX; i++ )
		for( j = startY+1; j <= endY; j++ ) {
			Hy[i][j][k] -= (dt/dx/mu0) * ex[k+1];
		}

	j = startY; 
	for( i = startX; i <= endX; i++ )
		for( k = startZ+1; k <= endZ; k++ ) {
			Hz[i][j][k] -= (dt/dx/mu0) * ex[k];
		}
	j = endY;
	for( i = startX; i <= endX; i++ )
		for( k = startZ+1; k <= endZ; k++ ) {
			Hz[i][j][k] += (dt/dx/mu0) * ex[k];
		}
}

int TFSF::getTFSFGrid() {
	return TFSFGrid;
}

int TFSF::getstartX() {
	return startX;
}

int TFSF::getstartY() {
	return startY;
}

int TFSF::getstartZ() {
	return startZ;
}

int TFSF::getendX() {
	return endX;
}

int TFSF::getendY() {
	return endY;
}

int TFSF::getendZ() {
	return endZ;
}