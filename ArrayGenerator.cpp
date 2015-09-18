#include "ArrayGenerator.h"
#include <iostream>
using namespace std;

int *ArrayGenerator::Alloc1DArray_int(int size) {
	int *array = new int [size];
	//cout << "[Debug] A 1D int array has been allocated." << endl;
	for (int i = 0; i < size; i++) {
		array[i] = 0;
	}
	//cout << "[Debug] A 1D int array has been initialized." << endl;
	return array;
}

double *ArrayGenerator::Alloc1DArray_double(int size) {
	double *array = new double [size];
	//cout << "[Debug] A 1D double array has been allocated." << endl;
	for (int i = 0; i < size; i++) {
		array[i] = 0;
	}
	//cout << "[Debug] A 1D int array has been initialized." << endl;
	return array;
}

int ***ArrayGenerator::Alloc3DArray_int(int size_x, int size_y, int size_z) {
	int ***array = new int **[size_x];
	for(int i = 0; i < size_x; i++) {
		array[i] = new int *[size_y];
		for(int j = 0; j < size_y; j++) {
			array[i][j] = new int [size_z];
		}
	}
	cout << "[Debug] 3D int array has been allocated" << endl;
	return array;
}

double ***ArrayGenerator::Alloc3DArray_double(int size_x, int size_y, int size_z) {
	double ***array = new double **[size_x];
	for(int i = 0; i < size_x; i++) {
		array[i] = new double *[size_y];
		for(int j = 0; j < size_y; j++) {
			array[i][j] = new double [size_z];
		}
	}
	cout << "[Debug] 3D double array has been allocated" << endl;
	return array;
}