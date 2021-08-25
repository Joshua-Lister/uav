#include "Circuit.h"
#include "utility.h"

Circuit::Circuit(std::vector<address_metadata>& centroids, bool empty) : route(centroids) {
	if (!empty)
	{
		this->route_size = this->route.size();
		//cout << "route_size circuit" << this->centroids.size() << "\n";
		route.resize(route_size);
		//velocity_v.resize(route_size - 1); // here
		mix(route);
		//route = centroids;
	}
	else
	{
		this->route_size = this->route.size();
		route.resize(route_size);
	}

};
Circuit::Circuit(clustering& c1) : route(c1.centroids) {
	route_size = route.size();
	//cout << "route_size circuit" << this->route_size << "\n";
	route.resize(route_size);
	velocity_v.resize(route_size - 1);
	masses.resize(route_size);
	mix(route);

}
//Circuit::Circuit(const Circuit& c_old)
//{
//	this->route_size = c_old.route_size;
//	this->route = c_old.centroids;
//
//}
//operator = (const Circuit& mat_old)
//{
//	if (this == &mat_old) return *this;
//
//}
Circuit::Circuit(int route_size) 
{
	route.resize(route_size);
};
Circuit::Circuit() {};
Circuit::~Circuit() {};

/***************************************************************************
The route except for the firstand last index is iteration upon.A generator 
outputs a random integer within the range of(increment, route size - 2) and 
swaps positions of route[i] and route[rand_int].
***************************************************************************/
void Circuit::mix(std::vector<address_metadata>& vec) {
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	int r_idx;
	std::default_random_engine generator(seed); // does it generate same thing every time
	for (int i = 1; i < route_size - 1; i++) {
		std::uniform_int_distribution<int> dist(i, route_size - 2);
		r_idx = dist(generator);
		std::swap(vec[i], vec[r_idx]);
	}
}

void Circuit::swap_addresses(std::vector<address_metadata>& c, const int& p1, const int& p2) 
{
	std::swap(c[p1], c[p2]);
}

//double Circuit::calc_mass(address_metadata& p1, address_metadata& p3) {
//	return (p1.x_coord - p3.x_coord) * (p1.x_coord - p3.x_coord) + (p1.y_coord - p3.y_coord) * (p1.y_coord - p3.y_coord);
//}

void Circuit::calc_masses() {
	for (size_t i = 1; i < route_size - 1; i++) 
		masses.push_back(util::length(route[i - 1], route[i + 1]));
}
void Circuit::calc_intial_velocities() {
	double temp_velocity = -1;
	for (int i = 0; i < route_size - 1; i++) {
		temp_velocity = util::length(route[i], route[i + 1]);
		this->velocity_v[i] = temp_velocity;// calc_mass(route[i], route[i + 1]);
	}
}

template <class Te>
double Circuit::return_v_sum(std::vector<Te>& vec) 
{
	return accumulate(vec.begin(), vec.end(), decltype(vec)::value_type(0));
}

/*********************************************************************************
A for loop in range(1, route _size - 1)  checks two routesand returns true if 
an element in both routes at the same index position is not equal to one another.
If the routes are the same then they are duplicated and false is returned.
*********************************************************************************/
bool Circuit::check_routes_duplicate(Circuit& obj1, Circuit& obj2) 
{
	for (int i = 1; i < route_size - 1; i++) {
		if (obj1.route[i].num != obj2.route[i].num)
			return true;
	}
	return false;
}

void Circuit::calc_velocities(Circuit& obj) 
{
	for (size_t i = 0; i < route_size; i++) 
	{
		this->velocity_v[i] = this->masses[i] - obj.masses[i] / this->masses[i] + obj.masses[i] * this->velocity_v[i] +
			2 * obj.masses[i] / this->masses[i] + obj.masses[i] * obj.velocity_v[i];
		obj.velocity_v[i] = 2 * this->masses[i] / this->masses[i] + obj.masses[i] * this->velocity_v[i] - this->masses[i] - 
			obj.masses[i] / this->masses[i] + obj.masses[i] * obj.velocity_v[i];
	}
}
bool Circuit::check_truck_drone_volume(const truck vehicle, const size_t no_of_drones, size_t& no_of_drone_missing) 
{
	if (vehicle.drone_capacity == no_of_drones)
		return true;
	no_of_drone_missing = vehicle.drone_capacity - no_of_drones;
	return false;
}
bool Circuit::check_if_complete(std::vector<address_metadata>& obj, std::vector<int>& undelivered_adr_id)
{
	for (auto const& adr : obj) {
		if (adr.visited == false) 
			undelivered_adr_id.push_back(adr.id);
	}
	if (undelivered_adr_id.size() == 0)
				return false;
	return true;
}
void Circuit::check_drone(std::vector<drone> drone_list) 
{

	for (auto& drone : drone_list)
		if (drone.battery_energy == 0) {
			if (drone.battery_swap == false)
				drone.out_of_use = true;
		}
		else {
			//auto x = drone::return_battery_energy_capacity();
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

/*********************************************************************************
The truck route is modelled on the travelling salesman problem.Therefore, except 
for the depot, a location cannot occur more than once in the route path. This 
function checks for any repeating locationand returns false if a location occurs 
more than onceand returns true if the routes only visit each location once.
*********************************************************************************/
bool Circuit::check_truck_route_validity() 
{
	for (int ic1 = 1; ic1 < route_size - 1; ic1++)
	{
		for (int ic2 = ic1 + 1; ic2 < route_size - 1; ic2++)
		{
			if (this->route[ic1].num == this->route[ic2].num)
			{
				return false;
			}
		}
	}
	return true;
}

