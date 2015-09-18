#ifndef CPML_H
#define CPML_H

class CPML {
private:
	double *B_e;
	double *B_h;
	double *C_e;
	double *C_h;
	double *kappa_e;
	double *kappa_h;

	void InitCPML(int size_CPML);

public:
	CPML(int size_CPML);
	~CPML();

	double *getB_e();
	double *getB_h();
	double *getC_e();
	double *getC_h();
	double *getkappa_e();
	double *getkappa_h();

};


#endif