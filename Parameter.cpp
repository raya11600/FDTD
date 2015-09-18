#include <cmath>
#include "Parameter.h"
using namespace std;

Parameter::Parameter() {
	// Basic physical parameters
	eps0 = 8.8541e-12;
	mu0 = 1.2566e-6; 
	PI = 3.1415926;
	lightspeed = 1 / sqrt(eps0*mu0); 
	imp0 = sqrt(mu0/eps0);

	// Space grid parameters
	x_domain = 0; //nm
	y_domain = 0; //nm
	z_domain = 0; //nm
	/*SIZE_X = x_domain/mesh;//+(15+20)*2,
	SIZE_Y = y_domain/mesh;//+(15+20)*2,
	SIZE_Z = z_domain/mesh+(20)*2;*/

	dx = 3.0*(1e-9);

	// Time grid parameters
	Courant = 0.5;
	dt = Courant / ( lightspeed * 1/dx );

	// CPML grid size
	CPMLGrid = 20;

	// Source & Totaltime
	SourceMode = 1;
		// Source=1: Sine Wave
		lambda = 0.85e-6  //Wave length
		T      = 11       //period you run

	// Structure parameters
	epsR = 1.0;
}