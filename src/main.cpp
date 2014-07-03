#include "lof.h"
#include <iostream>
#include <cmath>
using namespace std;

float getRand(float lo, float hi) {
	float r = lo
			+ static_cast<float>(rand())
					/ (static_cast<float>(RAND_MAX / (hi - lo)));
	return r;
}

int main() {
	const int k = 15;
	const int dimension = 2;
	const float threshold = 5;
	const int datasize = 500;
	const float hi = 5;
	const float lo = -5;
	float** p = new float*[datasize];

	lof ob_lof(k, dimension, threshold, datasize);
	srand(static_cast<unsigned>(time(0)));
	for (int i = 0; i < datasize - 1; ++i) {
		*p = new float[2];
		(*p)[0] = getRand(hi, lo);
		(*p)[1] = getRand(hi, lo);
		while (sqrt(pow((*p)[0], 2) + pow((*p)[1], 2)) > 5) {
			(*p)[0] = getRand(hi, lo);
			(*p)[1] = getRand(hi, lo);
		}
		ob_lof.add_data(*p);
	}
	*p = new float[2];
	(*p)[0] = 5;
	(*p)[1] = 5;
	ob_lof.add_data(*p);

	ob_lof.find_outlier();
}
