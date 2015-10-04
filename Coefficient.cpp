#include <stdio.h>
#include "Coefficient.h"
#include "ArrayGenerator.h"
using namespace std;

Coefficient::Coefficient() {
	Parameter param;
	int SIZE1D = param.SIZE1D;

	c_e = param.dt/(param.dx*param.eps0);
	c_h = param.dt/(param.dx*param.mu0);

	ArrayGenerator generator;
	Cex = generator.Alloc1DArray_double(SIZE1D);
	Chy = generator.Alloc1DArray_double(SIZE1D-1);

	Alloc3DArray();

	InitBasicCoef1D();
	InitBasicCoef3D();
}

void Coefficient::Alloc3DArray() {
	Parameter param;
	int SIZE_X = param.SIZE_X;
	int SIZE_Y = param.SIZE_Y;
	int SIZE_Z = param.SIZE_Z;

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
	Parameter param;
	int SIZE_X = param.SIZE_X;
	int SIZE_Y = param.SIZE_Y;
	int SIZE_Z = param.SIZE_Z;

	delete[] Cex; Cex = NULL;
	delete[] Chy; Chy = NULL;

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

void Coefficient::InitBasicCoef1D() {
	Parameter param;
	int SIZE1D = param.SIZE1D;

	// Coefficient for 1D update equation
	for(int i = 0; i < SIZE1D; i++) { 
		Cex[i] = c_e;
	}

	for(int i = 0; i < SIZE1D-1; i++) { 
		Chy[i] = c_h;
	}
}

void Coefficient::InitBasicCoef3D() {
	Parameter param;
	int SIZE_X = param.SIZE_X;
	int SIZE_Y = param.SIZE_Y;
	int SIZE_Z = param.SIZE_Z;

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
	for( int i = 0; i < SIZE1D; i++ ) {
		if( i >= 1 && i <= CPMLGrid ) {
			Cex[i] /= kappa_e[CPMLGrid-i];
		}
		if( i >= SIZE1D-1-CPMLGrid && i <= SIZE1D-2 ) {
			Cex[i] /= kappa_e[i-(SIZE1D-1-CPMLGrid)];
		}
	}

	for( int i = 0; i < SIZE1D-1; i++ ) {
		if( i >= 0 && i <= CPMLGrid-1 ) {
			Chy[i] /= kappa_h[(CPMLGrid-1)-i];
		}
		if( i >= SIZE1D-1-CPMLGrid && i <= SIZE1D-2 ) {
			Chy[i] /= kappa_h[i-(SIZE1D-1-CPMLGrid)];
		}
	}

}

void Coefficient::Init3DCoefWithCpml() {
	Parameter param;
	int SIZE_X = SIZE_X;
	int SIZE_Y = SIZE_Y;
	int SIZE_Z = SIZE_Z;

	CPML cpml;
	int CPMLGrid = cpml.getCPMLGrid();
	double *kappa_e = cpml.getkappa_e();
	double *kappa_h = cpml.getkappa_h();

	// Ex
	for( int i = 0; i < SIZE_X-1; i++ )
		for( int j = 1; j < SIZE_Y-1; j++ )
			for( int k = 1; k < SIZE_Z-1;k++) {
				// Cexz
				if( j >= 1 && j <= 1+CPMLGrid ) {
					Cexz[i][j][k] /= kappa_e[1+CPMLGrid-j];
				}
				if( j >= SIZE_Y-2-CPMLGrid && j <= SIZE_Y-2 ) {
					Cexz[i][j][k] /= kappa_e[j-(SIZE_Y-2-CPMLGrid)];
				}

				// Cexy
				if( k >= 1 && k <= 1+CPMLGrid ) {
					Cexy[i][j][k] /= kappa_e[1+CPMLGrid-k];
				}
				if( k >= SIZE_Z-2-CPMLGrid && k <= SIZE_Z-2 ) {
					Cexy[i][j][k] /= kappa_e[k-(SIZE_Z-2-CPMLGrid)];
				}
			}

	// Ey
	for( int i = 1; i < SIZE_X-1; i++ )
		for( int j = 0; j < SIZE_Y-1; j++ )
			for( int k = 1; k < SIZE_Z-1;k++) {
				// Ceyx
				if( k >= 1 && k <= 1+CPMLGrid ) {
					Ceyx[i][j][k] /= kappa_e[1+CPMLGrid-k];
				}
				if( k >= SIZE_Z-2-CPMLGrid && k <= SIZE_Z-2 ) {
					Ceyx[i][j][k] /= kappa_e[k-(SIZE_Z-2-CPMLGrid)];
				}

				// Ceyz
				if( i >= 1 && i <= 1+CPMLGrid ) {
					Ceyz[i][j][k] /= kappa_e[1+CPMLGrid-i];
				}
				if( i >= SIZE_X-2-CPMLGrid && i <= SIZE_X-2 ) {
					Ceyz[i][j][k] /= kappa_e[i-(SIZE_X-2-CPMLGrid)];
				}
			}

	// Ez
	for( int i = 1; i < SIZE_X-1; i++ )
		for( int j = 1; j < SIZE_Y-1; j++ )
			for( int k = 0; k < SIZE_Z-1;k++) {
				// Cezy
				if( i >= 1 && i <= 1+CPMLGrid ) {
					Cezy[i][j][k] /= kappa_e[1+CPMLGrid-i];
				}
				if( i >= SIZE_X-2-CPMLGrid && i <= SIZE_X-2 ) {
					Cezy[i][j][k] /= kappa_e[i-(SIZE_X-2-CPMLGrid)];
				}

				// Cezx
				if( j >= 1 && j <= 1+CPMLGrid ) {
					Cezx[i][j][k] /= kappa_e[1+CPMLGrid-j];
				}
				if( j >= SIZE_Y-2-CPMLGrid && j <= SIZE_Y-2 ) {
					Cezx[i][j][k] /= kappa_e[j-(SIZE_Y-2-CPMLGrid)];
				}
			}

	// Hx
	for( int i = 0; i < SIZE_X; i++ )
		for( int j = 0; j < SIZE_Y-1; j++ )
			for( int k = 0; k < SIZE_Z-1; k++ ) {
				// Chxz
				if( j >= 0 && j <= 0+CPMLGrid ) {
					Chxz[i][j][k] /= kappa_h[0+CPMLGrid-j];
				}
				if( j >= SIZE_Y-2-CPMLGrid && j <= SIZE_Y-2 ) {
					Chxz[i][j][k] /= kappa_h[j-(SIZE_Y-2-CPMLGrid)];
				}

				// Chxy
				if( k >= 0 && k <= 0+CPMLGrid ) {
					Chxy[i][j][k] /= kappa_h[0+CPMLGrid-k];
				}
				if( k >= SIZE_Z-2-CPMLGrid && k <= SIZE_Z-2 ) {
					Chxy[i][j][k] /= kappa_h[k-(SIZE_Z-2-CPMLGrid)];
				}
			}

	// Hy
	for( int i = 0; i < SIZE_X-1; i++ )
		for( int j = 0; j < SIZE_Y; j++ )
			for( int k = 0; k < SIZE_Z-1; k++ ) {
				// Chyx
				if( k >= 0 && k <= 0+CPMLGrid ) {
					Chyx[i][j][k] /= kappa_h[0+CPMLGrid-k];
				}
				if( k >= SIZE_Z-2-CPMLGrid && k <= SIZE_Z-2 ) {
					Chyx[i][j][k] /= kappa_h[k-(SIZE_Z-2-CPMLGrid)];
				}

				// Chyz
				if( i >= 0 && i <= 0+CPMLGrid ) {
					Chyz[i][j][k] /= kappa_h[0+CPMLGrid-i];
				}
				if( i >= SIZE_X-2-CPMLGrid && i <= SIZE_X-2 ) {
					Chyz[i][j][k] /= kappa_h[i-(SIZE_X-2-CPMLGrid)];
				}
			}

	// Hz
	for( int i = 0; i < SIZE_X-1; i++ )
		for( int j = 0; j < SIZE_Y-1; j++ )
			for( int k = 0; k < SIZE_Z; k++ ) {
				// Chzy
				if( i >= 0 && i <= 0+CPMLGrid ) {
					Chzy[i][j][k] /= kappa_h[0+CPMLGrid-i];
				}
				if( i >= SIZE_X-2-CPMLGrid && i <= SIZE_X-2 ) {
					Chzy[i][j][k] /= kappa_h[i-(SIZE_X-2-CPMLGrid)];
				}

				// Chzx
				if( j >= 0 && j <= 0+CPMLGrid ) {
					Chzx[i][j][k] /= kappa_h[0+CPMLGrid-j];
				}
				if( j >= SIZE_Y-2-CPMLGrid && j <= SIZE_Y-2 ) {
					Chzx[i][j][k] /= kappa_h[j-(SIZE_Y-2-CPMLGrid)];
				}
			}
}

void Coefficient::OutputCoef() {
	Parameter param;
	int SIZE1D = param.SIZE1D;

	// Warning: All size of for loops should be careful to read out.
	//          If any size of a for loop is larger than its array,
	//          it would increase the size of array automatically.
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
	for( int i = 0; i < SIZE1D-1; i++ ) {
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
