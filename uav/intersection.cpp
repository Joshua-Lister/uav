#include "intersection.h"

intersection::intersection(){}
intersection::~intersection(){}


double intersection::run_truck_tandem_drone(std::string drone_type)
{
	std::cout << "Running truck & tandem drone method with drone type " << drone_type << "\n";
	int additional_adr = 2;
	double max_flight_distance = 1000;// in metres
	double max_pay_load = 5;// in kg
	rural_drone arcadian_drone(max_pay_load, max_flight_distance);
	read_data rd("postal_data.txt");
	rd.fill_data();
	clustering cl(rd, max_flight_distance);
	cl.run_clustering();
	cl.add_depot();
	GA_param_list set_params;
	set_GA_params(set_params);
	genetic_algorithm<Circuit, address_metadata> tsp_ga(set_params, cl.centroids);
	result Result = tsp_ga.run_algorithm_genetic(&fitness, &initialise_circuit_v, &check_truck_route_validity);
	arcadian_drone.drone_multi_delivery(cl.k, additional_adr, cl.cluster_regions, Result.circuit_vector, max_pay_load, max_flight_distance);
	//arcadian_drone.drone_multi_delivery(cl.k, additional_adr, cl.cluster_regions,  Result.circuit_vector, )


	//truck t1(no_of_drones_req);
	




	return 0.0;
}

double intersection::comparison()
{
	return 1;
}
void intersection::do_tests()
{
	run_tests();
}

void intersection::run_charging_port_tandem_drone(std::string drone_type)
{
	std::cout << "Running drone & charging stations method with drone type " << drone_type << "\n";

}
