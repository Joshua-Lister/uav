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
	clustering(int c_size);
	clustering(const clustering& cp);
	~clustering();
	//inline static double length(const address_metadata& pg, const address_metadata& cd);
	//inline static double length(const address_metadata& adr, const double& x, const double& y);
	void set_rand_centroids(int k_val);
	void K_means(int k_val, vector<double>& distances);
	void coord_insert_sort(vector<address_metadata>& arg1);
	bool check_distances(vector<double>& check_d_v, double max_dist);
	void run_K_means();
	void group_clusters();
	void add_depot(address_metadata dep);
	void add_depot();
	void run_clustering();
	bool check_ids();
	static bool stopping_condition(const vector<address_metadata>& obj, const vector<address_metadata>& obj2);
	int k = 2;
	bool success;
	read_data d;
	double min_distance;
	vector<double> points;
	vector<double> distances;
	vector<size_t> no_of_points;
	vector<double> easting_sum, northing_sum;
	vector<address_metadata> centroids;
	vector<vector<address_metadata*>> cluster_regions;
	unordered_map<int, int> id_count;
	unordered_map<int, int> id_index_count;
	int idx = -1;
	int no_of_addresses = -1;
};

