#include "Circuit.h"

Circuit::Circuit(const vector<address_metadata>& centroids) : centroids(centroids) {
	route_size = centroids.size();
	route.resize(route_size);
	velocity_v.resize(route_size - 1);
	mix(route);
	//route = centroids;
	check_truck_route_validity(false);
};
Circuit::Circuit(const clustering& c1) : route(c1.centroids) {
	route_size = route.size();
	route.resize(route_size);
	velocity_v.resize(route_size - 1);
	masses.resize(route_size);
	mix(route);
	//route = centroids;
	check_truck_route_validity(false);
	cout << "working from circuit.cpp\n";
}
Circuit::Circuit() {};
Circuit::~Circuit() {};


//double Circuit::evaluation(int max_iterations, double tolerance) {
//	for (size_t iter_num = 0; iter_num < max_iterations; iter_num++) {
//		
//	}
//}
//template <class T>
void Circuit::mix(vector<address_metadata>& vec) {
	int seed = 42;
	default_random_engine generator(seed);
	for (int i = 0; i < route_size; i++) {
		uniform_int_distribution<int> dist(i, route_size - 1);
		int r_idx = dist(generator);
		swap_addresses(vec, i, r_idx);
	}
}
void Circuit::swap_addresses(vector<address_metadata>& c, const int& p1, const int& p2) {
	swap(c[p1], c[p2]);
}

//double Circuit::calc_mass(address_metadata& p1, address_metadata& p3) {
//	return (p1.x_coord - p3.x_coord) * (p1.x_coord - p3.x_coord) + (p1.y_coord - p3.y_coord) * (p1.y_coord - p3.y_coord);
//}

void Circuit::calc_masses() {
	for (size_t i = 1; i < route_size - 1; i++) 
		masses.push_back(calc::length(route[i - 1], route[i + 1]));
}
void Circuit::calc_intial_velocities() {
	double temp_velocity = -1;
	for (int i = 0; i < route_size - 1; i++) {
		temp_velocity = calc::length(route[i], route[i + 1]);
		this->velocity_v[i] = temp_velocity;// calc_mass(route[i], route[i + 1]);
	}
}

template <class Te>
double Circuit::return_v_sum(vector<Te>& vec) {
	return accumulate(vec.begin(), vec.end(), decltype(vec)::value_type(0));
}

bool Circuit::check_routes_duplicate(Circuit& obj1, Circuit& obj2) {
	for (int i = 1; i < route_size - 1; i++) {
		if (obj1.route[i].num != obj2.route[i].num)
			return true;
	}
	return false;
}

void Circuit::calc_velocities(Circuit& obj) {
	for (size_t i = 0; i < route_size; i++) {
		this->velocity_v[i] = this->masses[i] - obj.masses[i] / this->masses[i] + obj.masses[i] * this->velocity_v[i] +
			2 * obj.masses[i] / this->masses[i] + obj.masses[i] * obj.velocity_v[i];
		obj.velocity_v[i] = 2 * this->masses[i] / this->masses[i] + obj.masses[i] * this->velocity_v[i] - this->masses[i] - 
			obj.masses[i] / this->masses[i] + obj.masses[i] * obj.velocity_v[i];
	}
}
bool Circuit::check_truck_drone_volume(const truck vehicle, const size_t no_of_drones, size_t& no_of_drone_missing) {
	if (vehicle.drone_capacity == no_of_drones)
		return true;
	no_of_drone_missing = vehicle.drone_capacity - no_of_drones;
	return false;
}
bool Circuit::check_if_complete(vector<address_metadata>& obj, vector<int>& undelivered_adr_id){
	for (auto const& adr : obj) {
		if (adr.visited == false) 
			undelivered_adr_id.push_back(adr.id);
	}
	if (undelivered_adr_id.size() == 0)
				return false;
	return true;
}
void Circuit::check_drone(vector<drone> drone_list) {

	for (auto& drone : drone_list)
		if (drone.battery_energy == 0) {
			if (drone.battery_swap == false)
				drone.out_of_use = true;
		}
		else {
			auto x = drone::return_battery_energy_capacity();
			//drone.battery_energy = drone::return_battery_energy_capacity;
		}
		
}


//template <class T, class T1>
//bool Circuit::check_for_duplicate_post_codes(vector<T1>& obj) {
//	map<T, int> duplicate_post_codes;
//	for (const auto& adr : obj) {
//		auto post_code = duplicate_post_codes.insert(pair<T int>(adr.post_code, 1));
//		if (post_code.second == false)
//			post_code.first->second++;
//	}
//	for (const auto& post_code : duplicate_post_codes) {
//		if (post_code->second == 1)
//			post_code = duplicate_post_codes.erase(post_code);
//		else
//			post_code++;
//	}
//}

bool Circuit::check_truck_route_validity(bool verbose) {
	for (int ic1 = 0; ic1<centroids.size();ic1++)
	{
		for (int ic2 = ic1+1; ic2<centroids.size();ic2++)
			if (this->route[ic1].num == this->route[ic2].num)
			{
				if (verbose)
					cout << "Duplicate centroid found in truck route : " << this->centroids[ic1].id << " " << this->centroids[ic2].id << "\n";
				return false;
			}
	}

	/*auto duplicates = adjacent_find(this->centroids.begin() +1, this->centroids.end() -1);
	if (centroids.end() != duplicates)
	{
		cout << "Duplicate centroid found in truck route : " << duplicates->id << "\n";
		
		return false;
	}*/
	cout << "No duplicate centroid found in truck route\n";
	return true;
	// make standard IF
}

