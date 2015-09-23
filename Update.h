#ifndef UPDATE_H
#define	UPDATE_H

class Update {
private:
	// 1D Field;
	double *ex;
	double *hy;

	double *ex_now;
	double *ex_bef;

	// 1D psi function
	double *psi_ex;
	double *psi_hy;

	void Alloc1DArray();

	// 3D Field;
	double ***Ex;
	double ***Ey;
	double ***Ez;
	double ***Hx;
	double ***Hy;
	double ***Hz;
	
	void Alloc3DArray();

public:
	Update();
	~Update();

	void Update1Dfield_e(double *Cex, int t);
	void Update1Dfield_h(double *Chy, int t);

	void Update1DCpml_ex();
	void Update1DCpml_hy();

	double *getex();
	double *gethy();
};

#endif