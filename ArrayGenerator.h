#ifndef ARRAYGENERATOR_H
#define ARRAYGENERATOR_H

class ArrayGenerator {
public:
	int *Alloc1DArray_int(int size);
	double *Alloc1DArray_double(int size);

	int ***Alloc3DArray_int(int size_x, int size_y, int size_z);
	double ***Alloc3DArray_double(int size_x, int size_y, int size_z);
};


#endif