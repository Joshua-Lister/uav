//
////
#include "driver_code.h"
////
////vector<drone*> drones_v;
////
////extern int testnum, testval;
////double total_cost_rural(int num_of_drones, double drone_price, double truck_distance, double tot_drone_distance, double elec_price, double fuel_price)
////{
////	double total_drone_cost = num_of_drones * drone_price;
////	double total_fuel_cost = truck_distance * fuel_price;
////	double total_elec_cost = tot_drone_distance * elec_price;
////	return total_drone_cost + total_fuel_cost + total_elec_cost;
////}
////double total_cost_urban()
////{
////	return 0.0; //dummy
////}
////
//////void drone_operation(vector<drone>& drone_v)
//////{
//////	for (i : )
//////}
void set_GA_params(GA_param_list& lst)
{
	lst.generation_size = 40;
	lst.max_generation = 150;
	lst.crossover_prob = 0.85;
	lst.mutation_prob = 0.15;
	lst.seed = std::chrono::system_clock::now().time_since_epoch().count();
	lst.tolerance = 1.0e-3;
}
////
////double run_truck_tandem_drone(std::tring drone_type)
////{
////	/*cout << "Running truck & tandem drone method\n";
////	testnum = 1;
////	std::unique_ptr<drone> temp_drone_ptr = nullptr;
////	read_data tets("postal_data.txt");
////	testnum = 2;
////	tets.fill_data();
////	testnum = 3;
////	if (drone_type == "urban" || "Urban")
////		temp_drone_ptr = std::make_unique<urban_drone>(urban_drone(100., 5., 5., 1., 30, 6));
////	else if (drone_type == "rural" || "Rural") 
////		temp_drone_ptr = std::make_unique<rural_drone>(rural_drone(1., 1., 1., 1., 1., 1));
////	clustering cl(tets);
////	testnum = 4;
////	cl.run_K_means();
////	testnum = 5;
////	cl.group_clusters();
////	testnum = 6;
////	GA_param_list f;
////	testnum = 6;
////	set_GA_params(f);
////	testnum = 7;
////	genetic_algorithm<Circuit, address_metadata> vb(f, cl);
////	testnum = 8;*/
////	GA_param_list f;
////	testnum = 6;
////	set_GA_params(f);
////	std::vector<address_metadata> cl = set_dummy_route(6);
////	address_metadata depot;
////	depot.x_coord = 1.3, depot.y_coord = 1.3;
////	/*cl.add_depot(depot);
////	genetic_algorithm<Circuit, address_metadata> vb(f, cl.centroids);
////	result Result = vb.run_algorithm_genetic(10, &fitness, &initialise_circuit_v, &check_truck_route_validity);*/
////	/*double total_mass, total_distance;
////	int no_of_drones_req = drone_clusters(cl.k, 2, cl.cluster_regions, Result.circuit_vector,
////			temp_drone_ptr->maximum_payload_capacity, temp_drone_ptr->maxiumum_distance, total_distance, total_mass);
////
////	
////	setup_drones(no_of_drones_req, "rural");*/
////	//return total_cost_rural(no_of_drones_req, temp_drone_ptr->battery_energy, Result.optimal_performance,1 ,1 , 1);
////	return 1.0;
////
////	
////}
//////result try_result()
//////{
//////	/*GA_param_list f;
//////	testnum = 6;
//////	set_GA_params(f);
//////	vector<address_metadata> cl = set_dummy_route(25);
//////	address_metadata depot;
//////	depot.x_coord = 1.3, depot.y_coord = 1.3;
//////	cl.push_back(depot);
//////	cl.insert(cl.begin(), depot);
//////	genetic_algorithm<Circuit, address_metadata> vb(f, cl);
//////	result Result = vb.run_algorithm_genetic(25, &fitness, &initialise_circuit_v, &check_validity_dummy);
//////	return Result;*/
//////	return;
//////}
////void try_str()
////{
////	/*GA_param_list f;
////	testnum = 6;
////	set_GA_params(f);
////	testnum = 7;
////	extern string target_str;
////	genetic_algorithm<string, string> vb(f, target_str);
////	vb.run_algorithm_genetic(5, &string_fitness, &string_intialisation, &string_eval);*/
////}
