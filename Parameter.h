#ifndef PARAMETER_H
#define PARAMETER_H

class Parameter {
private:
	// Space grid parameters
	double mesh; //nm

	int x_domain; //nm
	int y_domain; //nm
	int z_domain; //nm

	// Time grid parameters
	double Courant;

public:
	// Basic physical parameters
	double eps0;
	double mu0;
	double PI;
	double lightspeed;
	double imp0;

	// Space grid parameters
	double dx;
	double dy;
	double dz;

	int SIZE_X;
	int SIZE_Y;
	int SIZE_Z;
	int SIZE1D;

	// Time grid parameters
	double dt;

	// Structure parameters
	double epsR;

private:
	void InitBasicParam();
	void InitSpaceParam();
	void InitTimeGrid();

public:
	Parameter();
	void OutputParam();
};

#endif