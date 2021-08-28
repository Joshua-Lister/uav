#pragma once
#include "rural_drone.h"
#include "truck.h"
#include "tsp_funcs.h"
#include <memory>

struct savings
{
	double energy_savings = 0;
	double petrol_savings = 0;
	int num_of_trucks_savings = 0;
	int num_of_drones_savings = 0;
};

class flight
{
public:
	flight(truck t1, double fuel_cost, double elec_cost, double max_flight_distance, double max_payload, std::string drone_type, GA_param_list& set_params);
	flight(truck t1, double max_flight_distance, double max_payload);
	~flight();
	std::tuple<double, double, int, int, int> multi_adr_drone_delivery(int k, std::vector<std::vector<address_metadata*>>& cl_data, 
		std::vector<address_metadata>& opt_route, double max_payload_cap, double max_dis);

	std::tuple<double, double, int, int>single_adr_drone_delivery(int k, std::vector<std::vector<address_metadata*>>& cl_data, 
		std::vector<address_metadata>& opt_route);

	 std::vector<savings> drone_method_savings(double max_payload, double max_flight_distance);

	 savings truck_only(bool verbose);

	 savings single_drone(bool verbose);

	 savings multi_drone(bool verbose);

	 std::vector<double> truck_vs_drone_savings();

	 double elec_cost;
	 double fuel_cost;
	 double max_flight_distance;
	 double max_payload;
	 
	 GA_param_list set_params;

	 std::string drone_type;
	//std::vector<std::shared_ptr<std::shared_ptr<int>>> v1;
	//std::vector<std::vector<std::shared_ptr<address_metadata>>> v10;
	std::vector<std::shared_ptr<drone>> v10;
	truck truck1;

};

