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

	Update updater(SIZE_Z);
	double *ex = updater.getex();
	double *hy = updater.gethy();
	cout << "[INFO] Initialized class Update." << endl;

	Coefficient coef(SIZE_Z);
	coef.Init1DCoefWithCpml(SIZE_Z);
	double *Cex = coef.getCex();
	double *Chy = coef.getChy();
	coef.OutputCoef(SIZE_Z);
	cout << "[INFO] Initialize class Coefficient" << endl;

	Source source;
	int Totaltime = source.gettotaltime();
	source.outputSettings();

	FILE *snapshot;
	snapshot = fopen("data.log","w");
	for( int k = 0; k < SIZE_Z; k++ ) {
		fprintf(snapshot, "%i ", k+1);
	}
	fprintf(snapshot, "\n");
	//cout << "[INFO] Start entering the time loop." << endl;
	for (int t = 0; t < 500; t++) {

		updater.Update1Dfield_e(Cex, SIZE_Z, t);

		updater.Update1DCpml_ex(SIZE_Z);

		updater.Update1Dfield_h(Chy, SIZE_Z-1, t);

		updater.Update1DCpml_hy(SIZE_Z-1);

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