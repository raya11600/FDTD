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
	Alloc1DArray();
	Alloc3DArray();
}

void Update::Alloc1DArray() {
	Parameter param;
	ArrayGenerator generator;

	ex = generator.Alloc1DArray_double(param.SIZE1D);
	hy = generator.Alloc1DArray_double(param.SIZE1D-1);

	ex_now = generator.Alloc1DArray_double(param.SIZE1D);
	ex_bef = generator.Alloc1DArray_double(param.SIZE1D);

	psi_ex = generator.Alloc1DArray_double(param.SIZE1D);
	psi_hy = generator.Alloc1DArray_double(param.SIZE1D-1);
}

void Update::Alloc3DArray() {
	Parameter param;
	int SIZE_X = param.SIZE_X;
	int SIZE_Y = param.SIZE_Y;
	int SIZE_Z = param.SIZE_Z;

	ArrayGenerator generator;

	Ex = generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y, SIZE_Z);
	Ey = generator.Alloc3DArray_double(SIZE_X, SIZE_Y-1, SIZE_Z);
	Ez = generator.Alloc3DArray_double(SIZE_X, SIZE_Y, SIZE_Z-1);
	Hx = generator.Alloc3DArray_double(SIZE_X, SIZE_Y-1, SIZE_Z-1);
	Hy = generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y, SIZE_Z-1);
	Hz = generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y-1, SIZE_Z);

	psi_Ex_Hz = generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y, SIZE_Z);
	psi_Ex_Hy = generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y, SIZE_Z);
	psi_Ey_Hx = generator.Alloc3DArray_double(SIZE_X, SIZE_Y-1, SIZE_Z);
	psi_Ey_Hz = generator.Alloc3DArray_double(SIZE_X, SIZE_Y-1, SIZE_Z);
	psi_Ez_Hy = generator.Alloc3DArray_double(SIZE_X, SIZE_Y, SIZE_Z-1);
	psi_Ez_Hx = generator.Alloc3DArray_double(SIZE_X, SIZE_Y, SIZE_Z-1);

	psi_Hx_Ez = generator.Alloc3DArray_double(SIZE_X, SIZE_Y-1, SIZE_Z-1);
	psi_Hx_Ey = generator.Alloc3DArray_double(SIZE_X, SIZE_Y-1, SIZE_Z-1);
	psi_Hy_Ex = generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y, SIZE_Z-1);
	psi_Hy_Ez = generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y, SIZE_Z-1);
	psi_Hz_Ey = generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y-1, SIZE_Z);
	psi_Hz_Ex = generator.Alloc3DArray_double(SIZE_X-1, SIZE_Y-1, SIZE_Z);

}

Update::~Update() {
	delete[] ex; ex = NULL;
	delete[] hy; hy = NULL;

	delete[] ex_now; ex_now = NULL;
	delete[] ex_bef; ex_bef = NULL;

	delete[] psi_ex; psi_ex = NULL;
	delete[] psi_hy; psi_hy = NULL;

	Parameter param;
	int SIZE_X = param.SIZE_X;
	int SIZE_Y = param.SIZE_Y;

	for( int i = 0; i < SIZE_X; i++ ) {
		for( int j = 0; j < SIZE_Y; j++ ) {
			if( i != SIZE_X-1 ) { 
				delete[] Ex[i][j];
				delete[] Hy[i][j];
			}
			if( j != SIZE_Y-1 ) {
				delete[] Ey[i][j];
				delete[] Hx[i][j];
			}
			delete[] Ez[i][j];
			if( i != SIZE_X-1 && j != SIZE_Y-1 ) {
				delete[] Hz[i][j];
			}
		}
		if( i != SIZE_X-1 ) {
			delete[] Ex[i];
			delete[] Hy[i];
			delete[] Hz[i];
		}
		delete[] Ey[i];
		delete[] Ez[i];
		delete[] Hx[i];
	}
	delete[] Ex; Ex = NULL;
	delete[] Ey; Ey = NULL;
	delete[] Ez; Ez = NULL;
	delete[] Hx; Hx = NULL;
	delete[] Hy; Hy = NULL;
	delete[] Hz; Hz = NULL;

	for( int i = 0; i < SIZE_X; i++ ) {
		for( int j = 0; j < SIZE_Y; j++ ) {
			if( i != SIZE_X-1 ) { 
				delete[] psi_Ex_Hz[i][j];
				delete[] psi_Ex_Hy[i][j];
				delete[] psi_Hy_Ex[i][j];
				delete[] psi_Hy_Ez[i][j];
			}
			if( j != SIZE_Y-1 ) {
				delete[] psi_Ey_Hx[i][j];
				delete[] psi_Ey_Hz[i][j];
				delete[] psi_Hx_Ez[i][j];
				delete[] psi_Hx_Ey[i][j];
			}
			delete[] psi_Ez_Hy[i][j];
			delete[] psi_Ez_Hx[i][j];
			if( i != SIZE_X-1 && j != SIZE_Y-1 ) {
				delete[] psi_Hz_Ey[i][j];
				delete[] psi_Hz_Ex[i][j];
			}
		}
		if( i != SIZE_X-1 ) {
			delete[] psi_Ex_Hz[i];
			delete[] psi_Ex_Hy[i];
			delete[] psi_Hy_Ex[i];
			delete[] psi_Hy_Ez[i];
			delete[] psi_Hz_Ey[i];
			delete[] psi_Hz_Ex[i];
		}
		delete[] psi_Ey_Hx[i];
		delete[] psi_Ey_Hz[i];
		delete[] psi_Ez_Hy[i];
		delete[] psi_Ez_Hx[i];
		delete[] psi_Hx_Ez[i];
		delete[] psi_Hx_Ey[i];

	}
	delete[] psi_Ex_Hz; psi_Ex_Hz = NULL;
	delete[] psi_Ex_Hy; psi_Ex_Hy = NULL;
	delete[] psi_Ey_Hx; psi_Ey_Hx = NULL;
	delete[] psi_Ey_Hz; psi_Ey_Hz = NULL;
	delete[] psi_Ez_Hy; psi_Ez_Hy = NULL;
	delete[] psi_Ez_Hx; psi_Ez_Hx = NULL;
	delete[] psi_Hx_Ez; psi_Hx_Ez = NULL;
	delete[] psi_Hx_Ey; psi_Hx_Ey = NULL;
	delete[] psi_Hy_Ex; psi_Hy_Ex = NULL;
	delete[] psi_Hy_Ez; psi_Hy_Ez = NULL;
	delete[] psi_Hz_Ey; psi_Hz_Ey = NULL;
	delete[] psi_Hz_Ex; psi_Hz_Ex = NULL;

}

void Update::Update1Dfield_e(double *Cex, int t) {
	Parameter param;
	int SIZE1D = param.SIZE1D;

	// Update e field
	for (int k = 1; k < SIZE1D-1; k++) {
		ex_now[k] = ex[k] - Cex[k] * ( hy[k] - hy[k-1] );
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
		hy[k] = hy[k] - Chy[k] * (ex[k+1] - ex[k]);
	}
}

void Update::Update1DCpml_ex(int CPMLGrid, double *B_e, double *C_e) {
	Parameter param;
	int SIZE1D = param.SIZE1D;

	for( int k = 1; k < SIZE1D-1; k++ ) {
		if( k >= 1 && k <= 1+CPMLGrid ) {
			psi_ex[k] = B_e[CPMLGrid+1-k] * psi_ex[k] + 
						C_e[CPMLGrid+1-k] * (hy[k] - hy[k-1]) / param.dx; 
			ex[k] = ex[k] - (param.dt/param.eps0) * psi_ex[k];
		}
		if( k >= SIZE1D-2-CPMLGrid && k <= SIZE1D-2 ) {
			psi_ex[k] = B_e[k-(SIZE1D-2-CPMLGrid)] * psi_ex[k]
					  + C_e[k-(SIZE1D-2-CPMLGrid)] * (hy[k] - hy[k-1]) / param.dx;
			ex[k] = ex[k] - (param.dt/param.eps0) * psi_ex[k];
		}
	}

}

void Update::Update1DCpml_hy(int CPMLGrid, double *B_h, double *C_h) {
	Parameter param;
	int SIZE1D = param.SIZE1D;

	for( int k = 0; k < SIZE1D-1; k++ ) {
		if( k >= 0 && k <= 0+CPMLGrid ) {
			psi_hy[k] = B_h[CPMLGrid-k] * psi_hy[k] +
						C_h[CPMLGrid-k] * (ex[k+1] - ex[k]) / param.dx;
			hy[k] = hy[k] - (param.dt/param.mu0) * psi_hy[k];
		}
		if( k >= SIZE1D-2-CPMLGrid && k <= SIZE1D-2 ) {
			psi_hy[k] = B_h[k-(SIZE1D-2-CPMLGrid)] * psi_hy[k] 
					  + C_h[k-(SIZE1D-2-CPMLGrid)] * (ex[k+1] - ex[k]) / param.dx;
			hy[k] = hy[k] - (param.dt/param.mu0) * psi_hy[k];
		}
	}

}

void Update::Update3Dfield_E(double ***Cexz, double ***Cexy, double ***Ceyx,
							 double ***Ceyz, double ***Cezy, double ***Cezx,
							 int t) {
	Parameter param;
	int SIZE_X = param.SIZE_X;
	int SIZE_Y = param.SIZE_Y;
	int SIZE_Z = param.SIZE_Z;

	for( int i = 0; i < SIZE_X-1; i++ )
		for( int j = 1; j < SIZE_Y-1; j++ )
			for( int k = 1; k < SIZE_Z-1;k++) {
				Ex[i][j][k] = Ex[i][j][k] 
							+ Cexz[i][j][k] * (Hz[i][j][k] - Hz[i][j-1][k]) 
							- Cexy[i][j][k] * (Hy[i][j][k] - Hy[i][j][k-1]);
			}

	for( int i = 1; i < SIZE_X-1; i++ )
		for( int j = 0; j < SIZE_Y-1; j++ )
			for( int k = 1; k < SIZE_Z-1; k++ ) {
				Ey[i][j][k] = Ey[i][j][k] 
							+ Ceyx[i][j][k] * (Hx[i][j][k] - Hx[i][j][k-1])
							- Ceyz[i][j][k] * (Hz[i][j][k] - Hz[i-1][j][k]);
			}

	for( int i = 1; i < SIZE_X-1; i++ )
		for( int j = 1; j < SIZE_Y-1; j++ )
			for( int k = 0; k < SIZE_Z-1; k++ ) {
				Ez[i][j][k] = Ez[i][j][k] 
							+ Cezy[i][j][k] * (Hy[i][j][k] - Hy[i-1][j][k])
							- Cezx[i][j][k] * (Hx[i][j][k] - Hx[i][j-1][k]);
			}

}

void Update::Update3Dfield_H(double ***Chxz, double ***Chxy, double ***Chyx,
							 double ***Chyz, double ***Chzy, double ***Chzx,
							 int t) {
	Parameter param;
	int SIZE_X = param.SIZE_X;
	int SIZE_Y = param.SIZE_Y;
	int SIZE_Z = param.SIZE_Z;

	if( t == 1 ) {
		Ex[SIZE_X/2][SIZE_Y/2][SIZE_Z/2] = 100;
	}

	for( int i = 0; i < SIZE_X; i++ )
		for( int j = 0; j < SIZE_Y-1; j++ )
			for( int k = 0; k < SIZE_Z-1; k++ ) {
				Hx[i][j][k] = Hx[i][j][k] 
							- Chxz[i][j][k] * (Ez[i][j+1][k] - Ez[i][j][k])
							+ Chxy[i][j][k] * (Ey[i][j][k+1] - Ey[i][j][k]);
			}

	for( int i = 0; i < SIZE_X-1; i++ )
		for( int j = 0; j < SIZE_Y; j++ )
			for( int k = 0; k <SIZE_Z-1; k++ ) {
				Hy[i][j][k] = Hy[i][j][k] 
							- Chyx[i][j][k] * (Ex[i][j][k+1] - Ex[i][j][k])
							+ Chyz[i][j][k] * (Ez[i+1][j][k] - Ez[i][j][k]);
			}

	for( int i = 0; i < SIZE_X-1; i++ )
		for( int j = 0; j < SIZE_Y-1; j++ )
			for( int k = 0; k < SIZE_Z; k++ ) {
				Hz[i][j][k] = Hz[i][j][k] 
							- Chzy[i][j][k] * (Ey[i+1][j][k] - Ey[i][j][k])
							+ Chzx[i][j][k] * (Ex[i][j+1][k] - Ex[i][j][k]);
			}

}

void Update::Update3DCpml_E(int CPMLGrid, double *B_e, double *C_e) {
	Parameter param;

	for( int i = 0; i < SIZE_X-1; i++ )
		for( int j = 1; j < SIZE_Y-1; j++ )
			for( int k = 1; k < SIZE_Z-1; k++ ) {
				// psi_Ex_Hz
				if( j >= 1 && j <= 1+CPMLGrid ) {
					psi_Ex_Hz[i][j][k] = B_e[1+CPMLGrid-j] * psi_Ex_Hz[i][j][k]
					  				   + C_e[1+CPMLGrid-j] * (Hz[i][j][k] - Hz[i][j-1][k]) / param.dy;
					
					Ex[i][j][k] += (param.dt/param.eps0) * psi_Ex_Hz[i][j][k];
				}

				if( j >= SIZE_Y-2-CPMLGrid && j <= SIZE_Z-2 ) {
					psi_Ex_Hz[i][j][k] = B_e[j-(SIZE_Y-2-CPMLGrid)] * psi_Ex_Hz[i][j][k]
									   + C_e[j-(SIZE_Y-2-CPMLGrid)] * (Hz[i][j][k] - Hz[i][j-1][k]) / param.dy;
					  
					Ex[i][j][k] += (param.dt/param.eps0) * psi_Ex_Hz[i][j][k]; }
				}
			
				// psi_Ex_Hy
				if( k >= 1 && k <= 1+CPMLGrid ) {
					psi_Ex_Hy[i][j][k] = B_e[1+CPMLGrid-k] * psi_Ex_Hy[i][j][k]
									   + C_e[1+CPMLGrid-k] * (Hy[i][j][k] - Hy[i][j][k-1]) / param.dz;

					Ex[i][j][k] -= (param.dt/param.eps0) * psi_Ex_Hy[i][j][k];
				}
				if( k >= SIZE_Z-2-CPMLGrid && k <= SIZE_Z-2 ) {
					psi_Ex_Hy[i][j][k] = B_e[k-(SIZE_Z-2-CPMLGrid)] * psi_Ex_Hy[i][j][k]
									   + C_e[k-(SIZE_Z-2-CPMLGrid)] * (Hy[i][j][k] - Hy[i][j][k-1]) / param.dz;

					Ex[i][j][k] -= (param.dt/param.eps0) * psi_Ex_Hy[i][j][k];
				}
			}

	for( int i = 1; i < SIZE_X-1; i++ )
		for( int j = 0; j < SIZE_Y; j++ )
			for( int k = 1; k < SIZE_Z-1; k++ ) {
				// psi_Ey_Hx
				if( k >= 1 && k <= 1+CPMLGrid ) {
					psi_Ey_Hx[i][j][k] = B_e[1+CPMLGrid-k] * psi_Ey_Hx[i][j][k]
									   + C_e[1+CPMLGrid-k] * (Hx[i][j][k] - Hx[i][j][k-1]) / param.dz;

					Ey[i][j][k] += (param.dt/param.eps0) * psi_Ey_Hx[i][j][k];
				}
				if( k >= SIZE_Z-2-CPMLGrid && k <= SIZE_Z-2 ) {
					psi_Ey_Hx[i][j][k] = B_e[k-(SIZE_Z-2-CPMLGrid)] * psi_Ey_Hx[i][j][k] +
									   + C_e[k-(SIZE_Z-2-CPMLGrid)] * (Hx[i][j][k] - Hx[i][j][k-1]) / param.dz;

					Ey[i][j][k] += (param.dt/param.eps0) * psi_Ey_Hx[i][j][k];
				}

				// psi_Ey_Hz
			}



}

void Update::Update3DCpml_H(int CPMLGrid, double *B_h, double *C_h) {

}

double *Update::getex() {
	return ex;
}

double *Update::gethy() {
	return hy;
}

double ***Update::getEx() {
	return Ex;
}

double ***Update::getEy() {
	return Ey;
}

double ***Update::getEz() {
	return Ez;
}

double ***Update::getHx() {
	return Hx;
}

double ***Update::getHy() {
	return Hy;
}

double ***Update::getHz() {
	return Hz;
}