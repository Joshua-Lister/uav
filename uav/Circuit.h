#pragma once
#include "Clustering.h"
#include <map>
#include <random>
#include <numeric>


class Circuit
{
public:
	Circuit(vector<address_metadata>& centroids);
	Circuit(clustering& c1);
	Circuit();
	~Circuit() ;

	static void swap_addresses(vector<address_metadata>& c, const int& p1, const int& p2);
	void mix(vector<address_metadata>& vec);
	double calc_mass(address_metadata& p1, address_metadata& p3);

	void calc_masses();

	void calc_intial_velocities();
	
	bool check_routes_duplicate(Circuit& obj1, Circuit& obj2);
	
	bool check_truck_drone_volume(const truck vehicle, const size_t no_of_drones, size_t& no_of_drone_missing);

	bool check_if_complete(vector<address_metadata>& obj, vector<int>& undelivered_adr_id);

	void check_drone(vector<drone> drone_list);

	bool check_truck_route_validity(bool verbose);

	double dist(vector<address_metadata>& circuit_vector);

	bool check_distance_validity();

	bool check_cluster_validty();

	template<class Te>
	double return_v_sum(vector<Te>& vec);

	void calc_velocities(Circuit& obj);
	double time = 0;
	double total_energy = 0;
	double total_distance_travelled = 0;
	vector<address_metadata> centroids;
	vector<address_metadata> route;
	vector<double> velocity_v;
	double mass_1, mass_2;
	double velocity_1, velocity_2;
	double velocity_1_p, velocity_2_p;
	double object_mass, object_velocity;
	vector<double> masses;
	inline static size_t route_size;


	//template<class T, class T1>
	//bool check_for_duplicate_post_codes(vector<T1>& obj);

};

