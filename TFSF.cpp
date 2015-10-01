#include <stdio.h>
#include "TFSF.h"
using namespace std;

TFSF::TFSF(int CPMLGrid) {
	TFSFGrid = CPMLGrid + 5;
}

TFSF::~TFSF() {

}

int TFSF::getTFSFGrid() {
	return TFSFGrid;
}