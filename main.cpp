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
	//int CPMLGrid = cpml.getCPMLGrid();
	cpml.OutputCPML();

	Coefficient coef;
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

	TFSF tfsf(&cpml);
	cout << "[INFO] Initialized class TFSF." << endl;

	FILE *snapshot;
	snapshot = fopen("ex.log","w");
	for( int k = 0; k < SIZE1D; k++ ) {
		fprintf(snapshot, "%i ", k+1);
	}
	fprintf(snapshot, "\n");
	//cout << "[INFO] Start entering the time loop." << endl;
	for (int t = 1; t < 1000; t++) {

		updater.Update1Dfield_e(t);

		tfsf.Add1DSource(ex, t);

		updater.Update1DCpml_ex();

		updater.Update3Dfield_E(t);
	
		updater.Update3DCpml_E();

		tfsf.AddTfsf_XYPlane_E(Ex, Ey, Ez, hy);
		//tfsf.AddTfsf_Box_E(Ex, Ey, Ez, hy);

		updater.Update1Dfield_h(t);

		updater.Update1DCpml_hy();

		updater.Update3Dfield_H(t);

		updater.Update3DCpml_H();

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