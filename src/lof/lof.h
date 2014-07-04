/*
 * lof.h
 *
 *  Created on: 2014/06/18
 *      Author: fukuda
 */

#ifndef LOF_H_
#define LOF_H_

#include <vector>
#include <list>
using namespace std;

class data {
public:
	float* coordinate;
	data** neighbors;
	float k_distance;
	float lrd;
	float lof;
	data() {
	}
	;
	data(float* coord, int k, int dimension);
};

class lof {
public:
	lof(int k, float dimension, float threshold, int datasize);
	~lof() {
	}
	;
	void find_outlier();
	void add_data(float* datapoint);
private:
	int datacount;
	data* dataset;
	int k;
	int dimension;
	float threshold;
	int datasize;
	void calc_neighbors();
	void calc_lrd();
	void calc_lof();
	void print_lof();
};

#endif /* LOF_H_ */
