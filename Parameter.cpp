#include <cmath>
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
	x_domain = 0; //nm
	y_domain = 0; //nm
	z_domain = 0; //nm
	
	SIZE_X = x_domain/mesh;//+(15+20)*2,
	SIZE_Y = y_domain/mesh;//+(15+20)*2,
	SIZE_Z = z_domain/mesh;//+(20)*2;

	mesh = 3.0; //nm
	dx = mesh * (1e-9);
}

void Parameter::InitTimeGrid() {
	// Time grid parameters
	Courant = 0.5;
	dt = Courant / ( lightspeed * 1/dx );
}
