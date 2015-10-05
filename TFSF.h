#ifndef TFSF_H
#define TFSF_H

#include "Source.h"
#include "CPML.h"

class TFSF : public Source {
protected:
	bool 	TFSFSwitch;
	int 	TFSFMode;
	int 	TFSFGrid;

	int 	startX;
	int 	startY;
	int 	startZ;
	int 	endX;
	int 	endY;
	int 	endZ;

public:
	TFSF();
	~TFSF();
	
	// 1D Source
	void Add1DSource(double *ex, int t);

	// XYPlane
		// TFSF boundary is just an x-y plane with no source end.
	void AddTfsf_XYPlane_E(double ***Ex, double ***Ey, double ***Ez, double *hy);
	void AddTfsf_XYPlane_H(double ***Hx, double ***Hy, double ***Hz, double *ex);

	// Box
		// TFSF boundary is like a rectangular box inside the field.
	void AddTfsf_Box_E(double ***Ex, double ***Ey, double ***Ez, double *hy);
	void AddTfsf_Box_H(double ***Hx, double ***Hy, double ***Hz, double *ex);
	
	int getTFSFGrid();
	int getstartX();
	int getstartY();
	int getstartZ();
	int getendX();
	int getendY();
	int getendZ();
};

#endif