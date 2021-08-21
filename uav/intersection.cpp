#include "intersection.h"

intersection::intersection(){}
intersection::~intersection(){}

void intersection::set_GA_params(GA_param_list& lst)
{}

double intersection::run_truck_tandem_drone(string drone_type)
{
	cout << "Running truck & tandem drone method\n";
	std::unique_ptr<drone> temp_drone_ptr = nullptr;
	read_data rd("postal_data.txt");
	rd.fill_data();
	clustering cl(rd);
	cl.run_clustering(depot);
	GA_param_list set_params;
	set_GA_params(set_params);
	genetic_algorithm<Circuit, address_metadata> tsp_ga(set_params, cl.centroids);
	tsp_ga.run_algorithm_genetic(&fitness, &initialise_circuit_v, &check_truck_route_validity);



	return 0.0;
}

void intersection::do_tests()
{
	run_tests();
}

void intersection::run_charging_port_tandem_drone()
{

}
