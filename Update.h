#ifndef UPDATE_H
#define	UPDATE_H

#include "Coefficient.h"
class Update : public Coefficient {
protected:
	// 1D Field;
	double *ex;
	double *hy;

private:
	double ex_bef_start;
	double ex_bef_end;

	// 1D psi function
	double *psi_ex;
	double *psi_hy;

	void Alloc1DArray();

protected:
	// 3D Field;
	double ***Ex;
	double ***Ey;
	double ***Ez;
	double ***Hx;
	double ***Hy;
	double ***Hz;

private:
	// 3D psi function
	double ***psi_Ex_Hz;
	double ***psi_Ex_Hy;
	double ***psi_Ey_Hx;
	double ***psi_Ey_Hz;
	double ***psi_Ez_Hy;
	double ***psi_Ez_Hx;

	double ***psi_Hx_Ez;
	double ***psi_Hx_Ey;
	double ***psi_Hy_Ex;
	double ***psi_Hy_Ez;
	double ***psi_Hz_Ey;
	double ***psi_Hz_Ex;
	
	void Alloc3DArray();

public:
	Update();
	~Update();

	void Update1Dfield_e(int t);
	void Update1Dfield_h(int t);

	void Update1DCpml_ex();
	void Update1DCpml_hy();

	void Update3Dfield_E(int t);
	void Update3Dfield_H(int t);

	void Update3DCpml_E();
	void Update3DCpml_H();

	void OutputEx_XYPlane(int t);
	void OutputEx_YZPlane(int t);

	double *getex();
	double *gethy();

	double ***getEx();
	double ***getEy();
	double ***getEz();
	double ***getHx();
	double ***getHy();
	double ***getHz();
};

#endif