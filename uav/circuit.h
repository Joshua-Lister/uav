#pragma once
#include "clustering.h"
#include "utility.h"
#include <map>
#include <random>
#include <numeric>


class Circuit
{
public:
	Circuit(std::vector<address_metadata>& centroids, bool empty);
	Circuit(clustering& c1);
	Circuit(int route_size);
	Circuit();
	~Circuit();

	static void swap_addresses(std::vector<address_metadata>& c, const int& p1, const int& p2);
	void mix(std::vector<address_metadata>& vec);
	double calc_mass(address_metadata& p1, address_metadata& p3);

	void calc_masses();

	void calc_intial_velocities();
	
	bool check_routes_duplicate(Circuit& obj1, Circuit& obj2);
	
	bool check_truck_drone_volume(const truck vehicle, const size_t no_of_drones, size_t& no_of_drone_missing);

	bool check_if_complete(std::vector<address_metadata>& obj, std::vector<int>& undelivered_adr_id);

	void check_drone(std::vector<drone> drone_list);


	bool check_truck_route_validity();

	double dist(std::vector<address_metadata>& circuit_vector);

	bool check_distance_validity();

	bool check_cluster_validty();

	template<class Te>
	double return_v_sum(std::vector<Te>& vec);

	void calc_velocities(Circuit& obj);
	double total_energy = 0;
	std::vector<address_metadata> route;
	std::vector<double> velocity_v;
	double mass_1, mass_2;
	double velocity_1, velocity_2;
	double velocity_1_p, velocity_2_p;
	double object_mass, object_velocity;
	std::vector<double> masses;
	inline static size_t route_size;


	//template<class T, class T1>
	//bool check_for_duplicate_post_codes(vector<T1>& obj);

};

