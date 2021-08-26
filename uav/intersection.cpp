#include "intersection.h"

intersection::intersection(){}
intersection::~intersection(){}


double intersection::run_truck_tandem_drone(std::string drone_type)
{
	//int all_distances, all_masses, number_of_addresses, number_of_drones;
	//std::tuple  <int, int, int, int>f;
	//f = std::make_tuple(all_distances, all_masses, number_of_addresses, number_of_drones);
	//std::cout << "Running truck & tandem drone method with drone type " << drone_type << "\n";
	//int additional_adr = 2;
	//double max_flight_distance = 200;// in metres
	//double max_pay_load = 12;// in kg
	//rural_drone arcadian_drone(max_pay_load, max_flight_distance);
	//read_data rd("postal_data.txt");
	//rd.fill_data();
	//clustering cl(rd, max_flight_distance);
	//cl.run_clustering();
	//cl.add_depot();
	//GA_param_list set_params;
	//set_GA_params(set_params);
	//genetic_algorithm<Circuit, address_metadata> tsp_ga(set_params, cl.centroids);
	//result Result = tsp_ga.run_algorithm_genetic(&fitness, &initialise_circuit_v, &check_truck_route_validity);
	//f = arcadian_drone.drone_multi_delivery(cl.k, additional_adr, cl.cluster_regions, Result.circuit_vector, max_pay_load, max_flight_distance);
	////arcadian_drone.drone_multi_delivery(cl.k, additional_adr, cl.cluster_regions,  Result.circuit_vector, )
	//std:: cout << std::get<0>(f) << "\n";	
	//std::cout << std::get<1>(f) << "\n";
	//std::cout << std::get<2>(f) << "\n";
	//std::cout << std::get<3>(f) << "\n";
	//std::tuple<double, int> g;

	//g = arcadian_drone.singular_flight(cl.k, cl.cluster_regions, Result.circuit_vector);
	//std:: cout << std::get<0>(g) << "\n";	
	//std::cout << std::get<1>(g) << "\n";
	//return 0;

	////truck t1(no_of_drones_req);
	




	return 0.0;
}

void intersection::set_parameters(double& elec_cost, double& fuel_cost, double& max_flight_distance, double& max_payload, int& truck_vol_capacity, std::string drone_choice)
{
	fuel_cost = (12 * 1000) / 1000; // Fuel cost per metre (M)
	elec_cost = (0.12 * 1000) / 1000; //Electricy cost per metre (M)
	max_flight_distance = 1050; //Metres (M)
	max_payload = 5; //Kilograms (KG)
	truck_vol_capacity = 25;
	drone_choice = "rural";
}

void intersection::set_GA_params_list(GA_param_list& lst)
{
	lst.generation_size = 40;
	lst.max_generation = 400;
	lst.crossover_prob = 0.8;
	lst.mutation_prob = 0.15;
	lst.seed = std::chrono::system_clock::now().time_since_epoch().count();
	lst.tolerance = 1.0e-3;
}
void intersection::run_which_linux()
{

	double elec_cost, max_flight_distance, max_payload, fuel_cost;
	int truck_vol_capacity;
	std::string drone_type;
	set_parameters(elec_cost, fuel_cost, max_flight_distance, max_payload, truck_vol_capacity, drone_type);
	truck t1(truck_vol_capacity);
	GA_param_list GA_list;
	flight f1(t1, elec_cost, fuel_cost, max_flight_distance, max_payload, drone_type, GA_list);
	
#ifdef TEST

	run_tests();

#elif MULTI
	
	savings multi_save = f1.multi_drone(false);

#elif SINGLE

	savings single_save = f1.single_drone(false);
	
#elif DRONE_COMPARE

	std::vector<savings> compare_d_v;
	compare_d_v = f1.drone_method_savings(f1.max_payload, f1.max_flight_distance);

 #elif ALL_COMPARE
  
  std::vector<double> compare_a_v(3);
  compare_a_v = f1.truck_vs_drone_savings();

#endif

}

void intersection::run_which_windows(std::string choice)
{
	double elec_cost, max_flight_distance, max_payload, fuel_cost;
	int truck_vol_capacity;
	std::string drone_choice;
	set_parameters(elec_cost, fuel_cost, max_flight_distance, max_payload, truck_vol_capacity, drone_choice);
	truck t1(truck_vol_capacity);
	std::string drone_type;
	GA_param_list GA_list;
	flight f1(t1, elec_cost, fuel_cost, max_flight_distance, max_payload, drone_type, GA_list);

	std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
	
	if (choice == "test")
	{
		run_tests();
	}

	else if (choice == "multi_drone")
	{
		savings multi_save = f1.multi_drone(false);
	}

	else if (choice == "single_drone")
	{
		savings single_save = f1.single_drone(false);
	}

	else if (choice == "drone_method_compare")
	{
		std::vector<savings> compare_d_v;
		compare_d_v = f1.drone_method_savings(f1.max_payload, f1.max_flight_distance);
	}

	else if (choice == "all_compare")
	{
		std::vector<double> compare_a_v(3);
		compare_a_v = f1.truck_vs_drone_savings();
	}
	else
	{
		std::cerr << "Incorrect string passed\n";
	}


}