#include "flight.h"

flight::flight(truck t1, double fuel_cost, double elec_cost, double max_flight_distance, double max_payload, std::string drone_type, GA_param_list& set_params) : truck1(t1)
{

}

flight::~flight()
{
	std::cout << "Many thanks to my supervisor Professor Stephen Neethling for his help and guidance throughout this project\n";
}

std::tuple<double, double, int, int, int> flight::multi_adr_drone_delivery(int k, std::vector<std::vector<address_metadata*>>& cl_data, std::vector<address_metadata>& opt_route, double max_payload_cap, double max_dist)
{
	int number_of_addresses = 0;
	int number_of_trucks = 0;
	int centroid_id, j, cnt_d, cnt_m, adr;
	int number_of_drones = 0;
	double sum_d, sum_m;
	double all_distances = 0, all_masses = 0;
	std::vector<double> distance_track;
	std::vector<double> mass_track;

	for (int i = 0; i < k; i++)
	{
		j = 0;
		adr = 0;
		cnt_d = 0;
		cnt_m = 1;
		centroid_id = opt_route[i].id;
		this->truck1.x_coord = &opt_route[i].x_coord;
		this->truck1.y_coord = &opt_route[i].y_coord;

		while (j < cl_data[centroid_id].size()) // j < size of cluster 
		{
			//std::vector<std::shared_ptr<address_metadata>> ptr;
			std::shared_ptr<drone> uav;
			if (cl_data[centroid_id].size() == 1) // if cluster size == 1 then can only visit the one address 
			{
				sum_d = 2 * util::length(opt_route[i], *cl_data[centroid_id][0]);
				sum_m = cl_data[centroid_id][0]->parcel_mass;
				cl_data[centroid_id][0]->visited = true;
				number_of_drones++;
				all_distances += sum_d;
				all_masses += sum_m;
				number_of_addresses++;
				uav = std::make_unique<rural_drone>(1, 1);
				uav->v1.push_back(cl_data[centroid_id][0]);
				this->v10.push_back(uav);
				break;
			}

			double d1, d2, m1;

			sum_d = 0; sum_m = 0;

			sum_d += util::length(opt_route[i], *cl_data[centroid_id][j]); // distance from centroid centre to first address
			distance_track.push_back(sum_d);
			sum_m += cl_data[centroid_id][adr]->parcel_mass;
			mass_track.push_back(sum_m);

			cl_data[centroid_id][j]->visited = true;
			
			j++;
			number_of_addresses++;
			bool constrained = false;

			while (!constrained)
			{
				if (adr == cl_data[centroid_id].size() - 1) // i use this to prevent index error at '*cl_data[centroid_id][adr + 1]'
				{
					double l = distance_track[cnt_d];// util::length(*cl_data[centroid_id][adr], opt_route[i]);
					sum_d += l;
					sum_m = std::accumulate(mass_track.begin(), mass_track.begin() + cnt_m, 0.);
				
					//sum_m += mass_track[cnt];
					//sum_m += cl_data[centroid_id][adr]->parcel_mass;
					cl_data[centroid_id][adr]->visited = true;
					break;
				}

				d1 = util::length(*cl_data[centroid_id][adr], *cl_data[centroid_id][adr + 1]); // calculating length between two addresses
				d2 = util::length(*cl_data[centroid_id][adr + 1], opt_route[i]); // calculating length from second address to centroid centre
				distance_track.push_back(d2);

				if (sum_d + d1 + d2 > max_dist) // if distance from centroid to first address + distance from adddress 1 to 2 + address 2 to centroid 
												 // is larger than drone maximum distance call this block
				{
					sum_d += distance_track[cnt_d]; // add to sum_d the distance from address 1 centroid
					sum_m = std::accumulate(mass_track.begin(), mass_track.begin() + cnt_m, 0.);
					cnt_d++;
					cnt_m++;//add to sum_m the mass for address 1
					constrained = true;
					adr++;
					break;
				}

				m1 = cl_data[centroid_id][adr + 1]->parcel_mass; //parcel mass
				mass_track.push_back(m1);

				if (sum_m + m1 > max_payload_cap) // if payload capacity constraint has been met
				{
					sum_d += distance_track[cnt_d]; // add to sum_d the distance from address 1 centroid
					sum_m = std::accumulate(mass_track.begin(), mass_track.begin() + cnt_m, 0.);
					cnt_d++;
					adr++;
					cnt_m++;//add to sum_m the mass for address 1
					constrained = true;
					break;
				}

				number_of_addresses++;
				cl_data[centroid_id][adr + 1]->visited = true;
				sum_d += d1; // adding distance between address one and two 
				sum_m += m1; // adding mass between address one and two
				adr++; //increment address count
				cnt_d++;
				cnt_m++; // cnt same as address but only accesses distance and mass track
				j++;

			}

			uav = std::make_unique<rural_drone>(1, 1);
			uav->v1.resize(adr);
			for (int i = 0; i < adr; i++)
			{
				uav->v1[i] = cl_data[centroid_id][i];
			}
			this->v10.push_back(uav);

			distance_track.clear();
			mass_track.clear();
			number_of_drones++; // when while(!constrained) breaks one drone used
			all_distances += sum_d; // adding total distance for that drone to all distances
			all_masses += sum_m; // adding total mass for that drone to all masses 
			//int lowest_num = std::min(temp_num_of_addresses_distance, temp_num_of_addresses_mass);
	 // adding number of address the drone could fly to
			cnt_d = 0;
			cnt_m = 1;// add number of address 
		}

	}

	int temp_drone_capacity = this->truck1.drone_capacity;
	while (number_of_drones > temp_drone_capacity)
	{
		number_of_trucks++;
		temp_drone_capacity *= 2;
	}

	return std::tuple<double, double, int, int, int>(all_distances, all_masses, number_of_addresses, number_of_drones, number_of_trucks);
}

std::tuple<double, double, int, int> flight::single_adr_drone_delivery(int k, std::vector<std::vector<address_metadata*>>& cl_data, std::vector<address_metadata>& opt_route)
{
	int centroid_id;
	int num_of_addresses = 0;
	int number_of_trucks = 0;
	double sum_d = 0;
	double total_parcel_mass = 0;
	for (int i = 0; i < k; i++)
	{
		centroid_id = opt_route[i].id;
		for (int j = 0; j < cl_data[centroid_id].size(); j++)
		{
			sum_d += 2 * util::length(opt_route[i], *cl_data[centroid_id][j]);
			num_of_addresses++;
			total_parcel_mass += cl_data[centroid_id][j]->parcel_mass;
		}
	}

	int temp_drone_capacity = this->truck1.drone_capacity;
	while (num_of_addresses > temp_drone_capacity)
	{
		number_of_trucks++;
		temp_drone_capacity *= 2;
	}
	
	return std::tuple<double, double, int, int>(sum_d, total_parcel_mass, num_of_addresses, number_of_trucks);
}

std::vector<savings> flight::drone_method_savings(double max_payload, double max_flight_distance)
{
	savings save_single, save_multi, save_dif;

	int all_distances1, all_masses1, number_of_addresses1, number_of_drones1, number_of_trucks1;
	int all_distances2, all_masses2, number_of_addresses2, number_of_drones2, number_of_trucks2;
	std::tuple<double, double, int, int, int> multi_drone_results;
	std::tuple<double, double, int, int> single_drone_results;
	std::cout << "Running truck & tandem drone method computing savings - singular drone flight to multiple drone flight using rural drone " << this->drone_type << "\n";
	//rural_drone arcadian_drone(max_payload, max_flight_distance);
	read_data rd("postal_data.txt");
	rd.fill_data();
	clustering cl(rd, max_flight_distance);
	cl.run_clustering();
	cl.add_depot();
	genetic_algorithm<Circuit, address_metadata> tsp_ga(this->set_params, cl.centroids);
	result Result = tsp_ga.run_algorithm_genetic(&fitness, &initialise_circuit_v, &check_truck_route_validity);
	multi_drone_results = multi_adr_drone_delivery(cl.k, cl.cluster_regions, Result.circuit_vector, max_payload, max_flight_distance);
	single_drone_results = single_adr_drone_delivery(cl.k, cl.cluster_regions, Result.circuit_vector);

	double energy_cost_multi = std::get<0>(multi_drone_results);
	double energy_cost_single = std::get<0>(single_drone_results);

	int trucks_multi = std::get<4>(multi_drone_results);
	int trucks_single = std::get<3>(single_drone_results);
	
	int drones_multi = std::get<3>(multi_drone_results);
	int drones_single = rd.data.size();

	save_single.energy_savings = energy_cost_single * this->elec_cost;
	save_single.num_of_trucks_savings = trucks_single;
	save_single.num_of_drones_savings = drones_single;
	save_single.petrol_savings = this->fuel_cost * Result.optimal_performance;

	save_multi.energy_savings = energy_cost_single * this->elec_cost;
	save_multi.num_of_trucks_savings = trucks_single;
	save_multi.num_of_drones_savings = drones_single;
	save_multi.petrol_savings = this->fuel_cost * Result.optimal_performance;


	save_dif.energy_savings = energy_cost_multi - energy_cost_single;
	save_dif.num_of_trucks_savings = trucks_multi - trucks_single;
	save_dif.num_of_drones_savings = drones_multi - drones_single;

	std::vector<savings> save_v(3);
	save_v[0] = save_single;
	save_v[1] = save_multi;
	save_v[2] = save_dif;
	
	return save_v;
	
}

savings flight::truck_only(bool verbose)
{
	if (verbose)
	{
		std::cout << "Running truck only delivery method\n";
	}

	savings save;
	read_data rd("postal_data.txt");
	rd.fill_data();
	clustering dummy_obj(rd);
	dummy_obj.add_depot();
	genetic_algorithm<Circuit, address_metadata> tsp_ga(this->set_params, dummy_obj.centroids);
	result Result = tsp_ga.run_algorithm_genetic(&fitness, &initialise_circuit_v, &check_truck_route_validity);
	double price = Result.optimal_performance * this->fuel_cost;
	save.petrol_savings = price;

	return save;

}

savings flight::single_drone(bool verbose)
{
	if (verbose)
	{
		std::cout << "Running single drone delivery method\n";
	}

	savings save;
	std::tuple<double, double, int, int> single_drone_results;
	read_data rd("postal_data.txt");
	rd.fill_data();
	clustering cl(rd, this->max_flight_distance);
	cl.run_clustering();
	cl.add_depot();
	genetic_algorithm<Circuit, address_metadata> tsp_ga(this->set_params, cl.centroids);
	result Result = tsp_ga.run_algorithm_genetic(&fitness, &initialise_circuit_v, &check_truck_route_validity);
	single_drone_results = single_adr_drone_delivery(cl.k, cl.cluster_regions, Result.circuit_vector);
	
	save.petrol_savings = this->fuel_cost *Result.optimal_performance;
	save.energy_savings = this->elec_cost * std::get<0>(single_drone_results);

	return save;

}

savings flight::multi_drone(bool verbose)
{
	if (verbose)
	{
		std::cout << "Running multi drone delivery method\n";
	}

	savings save;
	std::tuple<double, double, int, int, int> multi_drone_results;
	read_data rd("postal_data.txt");
	rd.fill_data();
	clustering cl(rd, this->max_flight_distance);
	cl.run_clustering();
	cl.add_depot();
	genetic_algorithm<Circuit, address_metadata> tsp_ga(set_params, cl.centroids);
	result Result = tsp_ga.run_algorithm_genetic(&fitness, &initialise_circuit_v, &check_truck_route_validity);
	multi_drone_results = multi_adr_drone_delivery(cl.k, cl.cluster_regions, Result.circuit_vector, max_payload, max_flight_distance);
	save.energy_savings = this->elec_cost * std::get<0>(multi_drone_results);
	save.petrol_savings = this->fuel_cost * Result.optimal_performance;
	save.num_of_drones_savings = std::get<3>(multi_drone_results);
	save.num_of_trucks_savings = std::get<4>(multi_drone_results);
	return save;

}

std::vector<double>flight::truck_vs_drone_savings()
{
	std::vector<savings> save_v(3);
	savings save = truck_only(false);
	std::cout << "Running savings comparison between truck only delivery and truck & drone tandem delivery\n";
	save_v = drone_method_savings(this->max_payload, this->max_flight_distance);
	double p1 = save.petrol_savings;
	double p2 = save_v[0].petrol_savings + save_v[0].energy_savings;
	double p3 = save_v[1].petrol_savings + save_v[1].energy_savings;
	std::vector<double> cost_v = { p1, p2, p3 };

#ifdef C_DATA
	std::ofstream myfile;
	myfile.open("savings_comparison.txt");
	myfile << "Truck Delivery Method £ " << "Single Flight Drone Delivery & Truck " << "Multi Flight Drone Delivery & Truck";
	myfile << std::endl;
	myfile << p1 << " " << p2 << " " << p3;
#endif C_DATA

	return cost_v;

}