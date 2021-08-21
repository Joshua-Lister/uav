#pragma once

#include "driver_code.h"

vector<drone*> drones_v;

extern int testnum, testval;
double total_cost_rural(int num_of_drones, double drone_price, double truck_distance, double tot_drone_distance, double elec_price, double fuel_price)
{
	double total_drone_cost = num_of_drones * drone_price;
	double total_fuel_cost = truck_distance * fuel_price;
	double total_elec_cost = tot_drone_distance * elec_price;
	return total_drone_cost + total_fuel_cost + total_elec_cost;
}
double total_cost_urban()
{
	return 0.0; //dummy
}
void setup_drones(int number_of_drones, string type)
{
	/*drones_v.resize(number_of_drones);
	if (type == "urban" || "Urban") {
		for (int i = 0; i < number_of_drones; i++) {
			drones_v[i] = new urban_drone();
		}
	}
	else if (type == "rural" || "Rural") {
		for (int i = 0; i < number_of_drones; i++) {
			drones_v[i] = new rural_drone();
		}
	}
	else
		cout << "Incorrect drone type entered\n";*/
}
//void drone_operation(vector<drone>& drone_v)
//{
//	for (i : )
//}
void set_GA_params(GA_param_list& lst)
{
	lst.generation_size = 20;
	lst.max_generation = 150;
	lst.crossover_prob = 0.5;
	lst.max_iterations = 30;
	lst.mutation_prob = 0.1;
	lst.seed = std::chrono::system_clock::now().time_since_epoch().count();
	lst.tolerance = 1.0e-3;
}
int drone_clusters(int k, int ad_adr, vector<vector<address_metadata*>>& cl_data, vector<address_metadata>& opt_route, double max_payload_cap,
	double max_dist, double& all_distances, double& all_masses)
{
	int cnt, cnt2, j;
	int centroid_id;
	int temp_num_of_addresses_distance = 0, temp_num_of_addresses_mass = 0;
	double sum_d, sum_m;
	all_distances = 0, all_masses = 0;
	int number_of_addresses = 0;
	vector<double> total_dist_v(ad_adr + 2);
	vector<double> cluster_mass_v(ad_adr + 1);

	for (int i = 0; i < k; i++)
	{ //Iterate over each cluster
		j = 0;
		centroid_id = opt_route[i].id;

		while (j < cl_data[i].size())
		{ //Iterate over all addresses with id i 
			
			cnt = 0;
			sum_m = 0;
			sum_d = 0;
			if (cl_data[i].size() - j < ad_adr)
			{
				break;
			}
			total_dist_v[cnt] = utility::length(opt_route[i], *cl_data[centroid_id][j]); //Calculate distance from centroid(id = i) to address with matching id
			for (int adr = j; adr < adr + ad_adr; adr++)
			{ //Iterate over user given part_size (potential maximum number of addresses a single drone can visit)
				// if cluster only contains one address this doesn't work
				total_dist_v[cnt] = utility::length(*cl_data[centroid_id][adr], *cl_data[centroid_id][adr + 1]); //Calculate distance between addresses
				cnt++;
			}
			total_dist_v[cnt] = utility::length(*cl_data[centroid_id][ad_adr + j], opt_route[i]); //Calculate distance from last address to centroid with matching id
			cnt = 0; //Assing cnt to 0 to reuse as iterating over parcel mass size now
			for (int adr = j; adr < j + ad_adr + 1; adr++)
			{ // ADD IF STATEMENT
				cluster_mass_v[cnt] = cl_data[centroid_id][adr]->parcel_mass; //Parcel mass of each address
				cnt++;
			}
			temp_num_of_addresses_distance = ad_adr + 1;
			temp_num_of_addresses_mass = ad_adr + 1;
			sum_d += std::accumulate(total_dist_v.begin(), total_dist_v.end(), 0.); //Calculate total distance 
			sum_m += std::accumulate(cluster_mass_v.begin(), cluster_mass_v.end(), 0.); //Calculate total mass 
			cnt = ad_adr; //Reusing cnt to iterate backwards
			while (sum_m > max_payload_cap)
			{ // iterate backwards over mass first as do not need to recalculate distance
				sum_m -= cluster_mass_v[cnt];
				temp_num_of_addresses_mass -= 1;
				cnt--;
			}
			//cnt2 = j + ad_adr - 1; // check this indexing
			if (temp_num_of_addresses_mass == 1)
				sum_d = 2. * utility::length(*cl_data[centroid_id][j], opt_route[i]); // check indexing

			else if (temp_num_of_addresses_mass == 0)
				sum_d = 0;

			else
			{//If payload capacity for a single drone has been met no need to recalculate distances
				cnt = ad_adr + 2;
				cnt2 = j + ad_adr - 1;
				while (sum_d > max_dist) 
				{
					sum_d -= total_dist_v[cnt];
					cnt--;
					sum_d -= total_dist_v[cnt];
					cnt--;
					sum_d += utility::length(*cl_data[centroid_id][cnt2], opt_route[i]);
					cnt2--;
					temp_num_of_addresses_distance -= 1;

				}
				int lowest_num = min(temp_num_of_addresses_distance, temp_num_of_addresses_mass);
				for (int k = j; k < lowest_num + j; k++)
					cl_data[i][k]->visited = true;

				all_distances += sum_d;
				all_masses += sum_m;
				number_of_addresses += lowest_num;
				j += lowest_num;
			}
		}

		return 1; // tmep
	}
}
double run_truck_tandem_drone(string drone_type)
{
	/*cout << "Running truck & tandem drone method\n";
	testnum = 1;
	std::unique_ptr<drone> temp_drone_ptr = nullptr;
	read_data tets("postal_data.txt");
	testnum = 2;
	tets.fill_data();
	testnum = 3;
	if (drone_type == "urban" || "Urban")
		temp_drone_ptr = std::make_unique<urban_drone>(urban_drone(100., 5., 5., 1., 30, 6));
	else if (drone_type == "rural" || "Rural") 
		temp_drone_ptr = std::make_unique<rural_drone>(rural_drone(1., 1., 1., 1., 1., 1));
	clustering cl(tets);
	testnum = 4;
	cl.run_K_means();
	testnum = 5;
	cl.group_clusters();
	testnum = 6;
	GA_param_list f;
	testnum = 6;
	set_GA_params(f);
	testnum = 7;
	genetic_algorithm<Circuit, address_metadata> vb(f, cl);
	testnum = 8;*/
	GA_param_list f;
	testnum = 6;
	set_GA_params(f);
	vector<address_metadata> cl = set_dummy_route(6);
	address_metadata depot;
	depot.x_coord = 1.3, depot.y_coord = 1.3;
	/*cl.add_depot(depot);
	genetic_algorithm<Circuit, address_metadata> vb(f, cl.centroids);
	result Result = vb.run_algorithm_genetic(10, &fitness, &initialise_circuit_v, &check_truck_route_validity);*/
	/*double total_mass, total_distance;
	int no_of_drones_req = drone_clusters(cl.k, 2, cl.cluster_regions, Result.circuit_vector,
			temp_drone_ptr->maximum_payload_capacity, temp_drone_ptr->maxiumum_distance, total_distance, total_mass);

	
	setup_drones(no_of_drones_req, "rural");*/
	//return total_cost_rural(no_of_drones_req, temp_drone_ptr->battery_energy, Result.optimal_performance,1 ,1 , 1);
	return 1.0;

	
}
result try_result()
{
	GA_param_list f;
	testnum = 6;
	set_GA_params(f);
	vector<address_metadata> cl = set_dummy_route(25);
	address_metadata depot;
	depot.x_coord = 1.3, depot.y_coord = 1.3;
	cl.push_back(depot);
	cl.insert(cl.begin(), depot);
	genetic_algorithm<Circuit, address_metadata> vb(f, cl);
	result Result = vb.run_algorithm_genetic(25, &fitness, &initialise_circuit_v, &check_validity_dummy);
	return Result;

}
void try_str()
{
	/*GA_param_list f;
	testnum = 6;
	set_GA_params(f);
	testnum = 7;
	extern string target_str;
	genetic_algorithm<string, string> vb(f, target_str);
	vb.run_algorithm_genetic(5, &string_fitness, &string_intialisation, &string_eval);*/
}
void run_charging_port_tandem_drone()
{
	cout << "Running drone & charging ports method\n";
	read_data tets("postal_data.txt");
	tets.fill_data();
}