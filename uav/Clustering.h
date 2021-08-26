#pragma once
#include "read_data.h"
#include <algorithm>
#include "drone.h"
#include "truck.h"
#include "utility.h"
#include <random>
#include <stdio.h>
#include <chrono>
#include <set>

class clustering
{
public:
	clustering(read_data& d, double max_distance);
	clustering(int c_size);
	clustering(read_data& d);
	clustering(const clustering& cp);
	~clustering();
	//inline static double length(const address_metadata& pg, const address_metadata& cd);
	//inline static double length(const address_metadata& adr, const double& x, const double& y);
	void set_rand_centroids(int k_val);
	void K_means(int k_val, std::vector<double>& distances);
	void coord_insert_sort(std::vector<address_metadata>& arg1);
	bool check_distances(std::vector<double>& check_d_v, double max_dist);
	void run_K_means();
	void group_clusters();
	void add_depot(address_metadata dep);
	void add_depot();
	void run_clustering();
	bool check_ids();
	static bool stopping_condition(const std::vector<address_metadata>& obj, const std::vector<address_metadata>& obj2);
	int k = 2;
	bool success;
	read_data d;
	double min_distance, max_distance;
	std::vector<double> points;
	std::vector<double> distances;
	std::vector<size_t> no_of_points;
	std::vector<double> easting_sum, northing_sum;
	std::vector<address_metadata> centroids;
	std::vector<std::vector<address_metadata*>> cluster_regions;
	std::unordered_map<int, int> id_count;
	std::unordered_map<int, int> id_index_count;
	int idx = -1;
	int no_of_addresses = -1;
};

