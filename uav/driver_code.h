#pragma once
#include "genetic_algorithm.h"
#include "drone.h"
#include "urban_drone.h"
#include "rural_drone.h"
#include "tsp_funcs.h"
#include "string_GA.cpp"
double total_cost_rural(int num_of_drones, double drone_price, double truck_distance, double tot_drone_distance, double elec_price, double fuel_price);
void setup_drones(int number_of_drones, string type);
void set_GA_params(GA_param_list& lst);
int drone_clusters(int k, int part_size, vector<unique_ptr<address_metadata>>& cl_data, vector<address_metadata>& opt_route, double max_payload_cap,
	double max_dist);
double run_truck_tandem_drone(string drone_type);
void try_str();
