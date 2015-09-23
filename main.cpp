#include <stdio.h>
#include <iostream>
#include <cmath>
#include "Update.h"
#include "Coefficient.h"
#include "Source.h"
#include "Parameter.h"
using namespace std;

Parameter param;
int SIZE_X = param.SIZE_X;
int SIZE_Y = param.SIZE_Y;
int SIZE_Z = param.SIZE_Z;
int SIZE1D = param.SIZE1D;


int main() {

	param.OutputParam();

	Source source;
	int Totaltime = source.gettotaltime();
	source.outputSettings();

	Coefficient coef;
	coef.Init1DCoefWithCpml();
	double *Cex = coef.getCex();
	double *Chy = coef.getChy();
	coef.OutputCoef();
	cout << "[INFO] Initialize class Coefficient" << endl;

	Update updater;
	double *ex = updater.getex();
	double *hy = updater.gethy();
	cout << "[INFO] Initialized class Update." << endl;

	FILE *snapshot;
	snapshot = fopen("data.log","w");
	for( int k = 0; k < SIZE_Z; k++ ) {
		fprintf(snapshot, "%i ", k+1);
	}
	fprintf(snapshot, "\n");
	//cout << "[INFO] Start entering the time loop." << endl;
	for (int t = 0; t < 500; t++) {

		updater.Update1Dfield_e(Cex, t);

		updater.Update1DCpml_ex();

		updater.Update1Dfield_h(Chy, t);

		updater.Update1DCpml_hy();

		for (int k = 0; k < SIZE_Z; k++) {
			fprintf(snapshot, "%g ", ex[k]);
		}
		fprintf(snapshot, "\n");

	}
	//cout << "[Debug] Time loop done." << endl;

	fclose(snapshot);
	//cout << "[Debug] snapshot done." << endl;
	snapshot = NULL;

	cout << "[INFO] Finished." << endl;
	return 0;
}