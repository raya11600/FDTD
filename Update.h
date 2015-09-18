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

public:
	Update(int size1D);
	~Update();

	void Update1Dfield_e(double *Cex, int gridsize, int t);
	void Update1Dfield_h(double *Chy, int gridsize, int t);

	void Update1DCpml_ex(int size, int size_CPML);
	void Update1DCpml_hy(int size, int size_CPML);

	double *getex();
	double *gethy();
};

#endif