#include <stdio.h>
#include <iostream>
#include <cmath>
#include "Update.h"
#include "Coefficient.h"
#include "Source.h"
#include "CPML.h"
#include "Parameter.h"
#include "TFSF.h"
using namespace std;

Parameter param;
int SIZE_X = param.SIZE_X;
int SIZE_Y = param.SIZE_Y;
int SIZE_Z = param.SIZE_Z;
int SIZE1D = param.SIZE1D;

void ShowProgress(int time_step);

int main() {

	param.OutputParam();

	Source source;
	int Totaltime = source.gettotaltime();
	source.outputSettings();

	CPML cpml;
	int CPMLGrid = cpml.getCPMLGrid();
	cpml.OutputCPML();
	double *B_e = cpml.getB_e();
	double *B_h = cpml.getB_h();
	double *C_e = cpml.getC_e();
	double *C_h = cpml.getC_h();

	Coefficient coef;
	//coef.Init1DCoefWithCpml();
	//coef.Init3DCoefWithCpml();
	double *Cex = coef.getCex();
	double *Chy = coef.getChy();
	double ***Cexz = coef.getCexz();
	double ***Cexy = coef.getCexy();
	double ***Ceyx = coef.getCeyx();
	double ***Ceyz = coef.getCeyz();
	double ***Cezy = coef.getCezy();
	double ***Cezx = coef.getCezx();

	double ***Chxz = coef.getChxz();
	double ***Chxy = coef.getChxy();
	double ***Chyx = coef.getChyx();
	double ***Chyz = coef.getChyz();
	double ***Chzy = coef.getChzy();
	double ***Chzx = coef.getChzx();
	coef.OutputCoef();
	cout << "[INFO] Initialize class Coefficient" << endl;

	Update updater;
	double *ex = updater.getex();
	double *hy = updater.gethy();
	double ***Ex = updater.getEx();
	double ***Ey = updater.getEy();
	double ***Ez = updater.getEz();
	double ***Hx = updater.getHx();
	double ***Hy = updater.getHy();
	double ***Hz = updater.getHz();
	cout << "[INFO] Initialized class Update." << endl;

	TFSF tfsf(CPMLGrid);
	cout << "[INFO] Initialized class TFSF." << endl;

	FILE *snapshot;
	snapshot = fopen("ex.log","w");
	for( int k = 0; k < SIZE_Z; k++ ) {
		fprintf(snapshot, "%i ", k+1);
	}
	fprintf(snapshot, "\n");
	//cout << "[INFO] Start entering the time loop." << endl;
	for (int t = 1; t < 1000; t++) {

		updater.Update1Dfield_e(Cex, t);

		tfsf.Add1DSource(ex, &source, t);

		updater.Update1DCpml_ex(CPMLGrid, B_e, C_e);

		updater.Update3Dfield_E(Cexz, Cexy, Ceyx, Ceyz, Cezy, Cezx, t);
	
		updater.Update3DCpml_E(CPMLGrid, B_e, C_e);

		tfsf.AddTfsf_XYPlane_E(Ex, Ey, Ez, hy);
		//tfsf.AddTfsf_Box_E(Ex, Ey, Ez, hy);

		updater.Update1Dfield_h(Chy, t);

		updater.Update1DCpml_hy(CPMLGrid, B_h, C_h);

		updater.Update3Dfield_H(Chxz, Chxy, Chyx, Chyz, Chzy, Chzx, t);

		updater.Update3DCpml_H(CPMLGrid, B_h, C_h);

		tfsf.AddTfsf_XYPlane_H(Hx, Hy, Hz, ex);
		//tfsf.AddTfsf_Box_H(Hx, Hy, Hz, ex);

		for (int k = 0; k < SIZE1D; k++) {
			fprintf(snapshot, "%g ", ex[k]);
		}
		fprintf(snapshot, "\n");
		
		updater.OutputEx_YZPlane(t);

		ShowProgress(t);

	}
	//cout << "[Debug] Time loop done." << endl;

	fclose(snapshot);
	//cout << "[Debug] snapshot done." << endl;
	snapshot = NULL;

	cout << "[INFO] Finished." << endl;
	return 0;
}

void ShowProgress(int time_step) {
	int percent = (int)floor(100 * (time_step+1)/1000);
	static int A = 0;

	if( time_step == 1 ) {
		cout << percent << "%" << endl;
	}
	else if( time_step > 1 && percent > A ) {
		cout << percent << "%" << endl;
	}
	A = percent;
}