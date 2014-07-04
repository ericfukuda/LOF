/*
 * lof.cpp
 *
 *  Created on: 2014/06/18
 *      Author: fukuda
 */

#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <cfloat>
#include <limits>
#include "lof.h"
using namespace std;

data::data(float* coord, int k, int dimension) {
	k_distance = 0.0;
	lrd = 0.0;
	lof = 0.0;
	coordinate = new float[dimension];
	for (int i = 0; i < dimension; ++i) {
		coordinate[i] = coord[i];
	}
	neighbors = new data*[k];
}

lof::lof(int k, float dimension, float threshold, int datasize) {
	this->k = k;
	this->dimension = dimension;
	this->threshold = threshold;
	this->datasize = datasize;
	datacount = 0;
	dataset = new data[datasize];
}

void lof::add_data(float* datapoint) {
	dataset[datacount] = data(datapoint, k, dimension);
	++datacount;
}

void lof::calc_neighbors() {
	for (int i = 0; i < datasize; ++i) {
		float distances[k];
		for (int n = 0; n < k; ++n) {
			distances[n] = numeric_limits<float>::max();
		}
		for (int j = 0; j < datasize; ++j) {
			if (i == j)
				continue;
			float dist = 0;
			for (int l = 0; l < dimension; ++l) {
				dist += pow(dataset[i].coordinate[l] - dataset[j].coordinate[l],
						2);
			}
			dist = sqrt(dist);
			for (int l = 0; l < k; ++l) {
				if (distances[l] > dist) {
					for (int m = k - 1; m > l; --m) {
						distances[m] = distances[m - 1];
						dataset[i].neighbors[m] = dataset[i].neighbors[m - 1];
					}
					distances[l] = dist;
					dataset[i].neighbors[l] = &(dataset[j]);
					break;
				}
			}
		}
		dataset[i].k_distance = distances[k - 1];
	}
}

void lof::calc_lrd() {
	for (int i = 0; i < datasize; ++i) {
		float reach_dist = 0;
		for (int j = 0; j < k; ++j) {
			float dist = 0;
			for (int l = 0; l < dimension; ++l) {
				dist += pow(
						dataset[i].coordinate[l]
								- dataset[i].neighbors[j]->coordinate[l], 2);
			}
			dist = sqrt(dist);
			reach_dist += (
					(dist > dataset[i].neighbors[j]->k_distance) ?
							dist : dataset[i].neighbors[j]->k_distance);
		}
		dataset[i].lrd = (float) k / reach_dist;
	}
}

void lof::calc_lof() {
	for (int i = 0; i < datasize; ++i) {
		for (int j = 0; j < k; ++j) {
			dataset[i].lof += dataset[i].neighbors[j]->lrd;
		}
		dataset[i].lof /= dataset[i].lrd;
		dataset[i].lof /= (float) k;
	}
}

void lof::print_lof() {
	for (int i = 0; i < datasize; ++i) {
		cout << dataset[i].lof << endl;
	}
}

void lof::find_outlier() {
	calc_neighbors();
	calc_lrd();
	calc_lof();
	print_lof();
	float max_lof = 0;
	for (int i = 0; i < datasize; ++i) {
		if (dataset[i].lof > max_lof) {
			max_lof = dataset[i].lof;
		}
	}
	cout << max_lof << endl;
}
