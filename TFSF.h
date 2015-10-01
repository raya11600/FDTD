#ifndef TFSF_H
#define TFSF_H

class TFSF {
private:
	int TFSFGrid;

	int startX;
	int startY;
	int startZ;

public:
	TFSF();
	~TFSF();

	void AddTfsf2Sides_E(double ***Ex, double ***Ey, double ***Ez, double *hy);
	void AddTfsf2Sides_H(double ***Hx, double ***Hy, double ***Hz, double *ex);

	void TFSF::AddTfsf6Sides_E();
	void TFSF::AddTfsf6Sides_H();
	
	int getTFSFGrid();
};

#endif