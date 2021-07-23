#pragma once
#include "read_data.h"
#include <algorithm>
#include "drone.h"
#include "truck.h"
#include "calc.h"
class clustering
{
public:
	clustering(size_t epochs, size_t k, read_data& d);
	~clustering();
	//inline static double length(const address_metadata& pg, const address_metadata& cd);
	//inline static double length(const address_metadata& adr, const double& x, const double& y);
	void set_rand_centroids();
	void K_means();
	void run_K_means();
	bool stopping_condition(address_metadata const& obj, address_metadata const& obj2);
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

