#include <stdio.h>
#include <iostream>
#include <cmath>
#include "Update.h"
#include "Coefficient.h"
using namespace std;

int SIZE_X = 100;
int SIZE_Y = 100;
int SIZE_Z = 100;
int CPMLGrid = 20;

int main() {

	Update updater(SIZE_Z);
	cout << "[INFO] Initialized class Update." << endl;

	Coefficient coef(SIZE_Z);
	coef.Init1DCoefWithCpml(SIZE_Z, CPMLGrid);
	double *Cex = coef.getCex();
	double *Chy = coef.getChy();
	cout << "[INFO] Initialize class Coefficient" << endl;

	FILE *snapshot;
	snapshot = fopen("data.log","w");
	//cout << "[INFO] Start entering the time loop." << endl;
	for (int t = 0; t < 500; t++) {

		updater.Update1Dfield_e(Cex, SIZE_Z, t);

		updater.Update1DCpml_ex(SIZE_Z, CPMLGrid);

		updater.Update1Dfield_h(Chy, SIZE_Z-1, t);

		updater.Update1DCpml_hy(SIZE_Z-1, CPMLGrid);

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