#include <cmath>
#include <stdio.h>
#include "Parameter.h"
using namespace std;

Parameter::Parameter() {
	InitBasicParam();
	InitSpaceParam();
	InitTimeGrid();

	// Structure parameters
	epsR = 1.0;
}

void Parameter::InitBasicParam() {
	// Basic physical parameters
	eps0 = 8.8541e-12;
	mu0 = 1.2566e-6; 
	PI = 3.1415926;
	lightspeed = 1 / sqrt(eps0*mu0); 
	imp0 = sqrt(mu0/eps0);
}

void Parameter::InitSpaceParam() {
	// Space grid parameters
	mesh = 3.0; //nm
	dx = mesh * (1e-9);

	x_domain = 300; //nm
	y_domain = 300; //nm
	z_domain = 300; //nm
	
	SIZE_X = (int)round(x_domain/mesh);//+(15+20)*2,
	SIZE_Y = (int)round(y_domain/mesh);//+(15+20)*2,
	SIZE_Z = (int)round(z_domain/mesh);//+(20)*2;

	SIZE1D = SIZE_Z;
}

void Parameter::InitTimeGrid() {
	// Time grid parameters
	Courant = 0.5;
	dt = Courant / ( lightspeed * 1/dx );
}

void Parameter::OutputParam() {
	FILE *file;
	file = fopen("parameter.data","w");
	fprintf(file, "----- Basic parameter -----\n");
	fprintf(file, "eps0 = %g\n", eps0);
	fprintf(file, "mu0  = %g\n", mu0);
	fprintf(file, "PI   = %g\n", PI);
	fprintf(file, "lightspeed = %g\n", lightspeed);
	fprintf(file, "imp0 = %g\n", imp0);
	fprintf(file, "\n");
	fprintf(file, "----- Space grid -----\n");
	fprintf(file, "mesh = %g nm\n", mesh);
	fprintf(file, "dx   = %g m\n", dx);
	fprintf(file, "\n");
	fprintf(file, "x_domain = %i nm\n", x_domain);
	fprintf(file, "y_domain = %i nm\n", y_domain);
	fprintf(file, "z_domain = %i nm\n", z_domain);
	fprintf(file, "SIZE_X = %i\n", SIZE_X);
	fprintf(file, "SIZE_Y = %i\n", SIZE_Y);
	fprintf(file, "SIZE_Z = %i\n", SIZE_Z);
	fprintf(file, "SIZE1D = %i\n", SIZE1D);
	fprintf(file, "\n");
	fprintf(file, "----- Time grid -----\n");
	fprintf(file, "Courant = %g\n", Courant);
	fprintf(file, "dt = %g\n", dt);
	fprintf(file, "\n");
	fprintf(file, "----- Structure -----\n");
	fprintf(file, "epsR = %g\n", epsR);
	fprintf(file, "\n");
	fclose(file);
	file = NULL;
}