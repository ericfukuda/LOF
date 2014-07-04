/*
 * data_generator.cpp
 *
 *  Created on: 2014/07/03
 *      Author: fukuda
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "data_generator.h"
using namespace std;

float genRand(float lo, float hi) {
	float r = lo
			+ static_cast<float>(rand())
					/ (static_cast<float>(RAND_MAX / (hi - lo)));
	return r;
}

void getrand_in_circle(const float center, const float radius,
		float* coordinate) {
	coordinate[0] = genRand(center + radius, center - radius);
	coordinate[1] = genRand(center + radius, center - radius);
	while (sqrt(pow(coordinate[0], 2) + pow(coordinate[1], 2)) > radius) {
		coordinate[0] = genRand(center + radius, center - radius);
		coordinate[1] = genRand(center + radius, center - radius);
	}
}

int main(int argc, char** argv) {
	const float center = 5;
	const float radius = 5;
	ofstream fout(argv[1]);
	if (!fout) {
		cout << "File open failed.\n";
		return 1;
	}

	for (int i = 0; i < 100; i++) {
		float coordinate[2];
		getrand_in_circle(center, radius, coordinate);
		fout << coordinate[0] << '\t' << coordinate[1] << endl;
		cout << coordinate[0] << '\t' << coordinate[1] << endl;
	}
	fout << 10.0 << '\t' << 10.0 << endl;
	cout << 10.0 << '\t' << 10.0 << endl;
	fout << 10.0 << '\t' << 9.0 << endl;
	cout << 10.0 << '\t' << 9.0 << endl;

	fout.close();
}
