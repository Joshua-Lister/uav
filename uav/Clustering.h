#pragma once
#include "read_data.h"
#include <algorithm>
#include "drone.h"
#include "truck.h"
#include "utility.h"
#include <cmath>
#include <random>
#include <stdio.h>
#include <chrono>
#include <set>
class clustering
{
public:
	clustering(read_data& d);
	clustering();
	~clustering();
	//inline static double length(const address_metadata& pg, const address_metadata& cd);
	//inline static double length(const address_metadata& adr, const double& x, const double& y);
	void set_rand_centroids(int k_val);
	void K_means(int k_val, vector<float>& distances, bool verbose);
	void coord_sort(vector<address_metadata>& arg1);
	bool check_distances(vector<float>& check_d_v);
	void run_K_means();
	bool check_ids(bool verbose);
	bool stopping_condition(const vector<address_metadata>& obj, const vector<address_metadata>& obj2);
	size_t epochs, k;
	bool success;
	read_data d;
	double min_distance;
	vector<double> points;
	vector<double> distances;
	vector<size_t> no_of_points;
	vector<double> easting_sum, northing_sum;
	vector<address_metadata> centroids, centroid_track;
	int idx = -1;
	int no_of_addresses = -1;
};

