#include "rural_drone.h"
//
//rural_drone::rural_drone(double maximum_battery_time, double maximum_payload_capacity, double drone_mass, double payload, double max_flight_time,
//int rotors){}
rural_drone::rural_drone(double maximum_battery_time, double maximum_payload_capacity, double drone_mass, double payload, double max_flight_time,
	int rotors) : drone(){}

rural_drone::rural_drone() : drone() {}

rural_drone::~rural_drone(){}

//bool rural_drone::energy_flight_constraint(double L)
//{
//	/*double energy1 = power_consumption() * (L / horizontal_max_velocity);
//	double dist_to_truck = utility::length(adr, this->x_coord, this->y_coord);*/
//	return true;
//}
//
//std::tuple<int, int, int, int> rural_drone::drone_multi_delivery(int k, int ad_adr, vector<vector<address_metadata*>>& cl_data, vector<address_metadata>& opt_route, double max_payload_cap, double max_dist)
//{
//	//int cnt, cnt2, j;
//	//int centroid_id;
//	//int number_of_drones = 0;
//	//int number_of_addresses = 0;
//	//int temp_num_of_addresses_distance = 0, temp_num_of_addresses_mass = 0;
//	//
//	//double sum_d, sum_m;
//	//double all_distances = 0, all_masses = 0;
//	//
//	//vector<double> total_dist_v(ad_adr + 2);
//	//vector<double> cluster_mass_v(ad_adr + 1);
//
//	//for (int i = 0; i < k; i++)
//	//{ //Iterate over each cluster
//	//	j = 0;
//
//	//	centroid_id = opt_route[i].id;
//
//	//	while (j < cl_data[i].size())
//	//	{ //Iterate over all addresses with id i
//	//		
//	//		int gap_size = cl_data[i].size() - j;
//	//		
//	//		if (gap_size < ad_adr)
//	//		{
//	//			ad_adr = gap_size;
//	//		}
//
//	//		cnt = 0;
//	//		sum_m = 0;
//	//		sum_d = 0;
//
//	//		total_dist_v[cnt] = utility::length(opt_route[i], *cl_data[centroid_id][j]); //Calculate distance from centroid(id = i) to address with matching id
//	//		
//	//		for (int adr = j; adr < j + ad_adr; adr++)
//	//		{ //Iterate over user given part_size (potential maximum number of addresses a single drone can visit)
//	//			// if cluster only contains one address this doesn't work
//	//			total_dist_v[cnt] = utility::length(*cl_data[centroid_id][adr], *cl_data[centroid_id][adr + 1]); //Calculate distance between addresses
//	//			cnt++;
//	//		}
//	//		
//	//		total_dist_v[cnt] = utility::length(*cl_data[centroid_id][ad_adr + j], opt_route[i]); //Calculate distance from last address to centroid with matching id
//	//		
//	//		cnt = 0; //Assing cnt to 0 to reuse as iterating over parcel mass size now
//	//		for (int adr = j; adr < j + ad_adr + 1; adr++)
//	//		{ // ADD IF STATEMENT
//	//			cluster_mass_v[cnt] = cl_data[centroid_id][adr]->parcel_mass; //Parcel mass of each address
//	//			cnt++;
//	//		}
//	//		
//	//		temp_num_of_addresses_distance = ad_adr + 1;
//	//		temp_num_of_addresses_mass = ad_adr + 1;
//	//		sum_d += std::accumulate(total_dist_v.begin(), total_dist_v.end(), 0.); //Calculate total distance 
//	//		sum_m += std::accumulate(cluster_mass_v.begin(), cluster_mass_v.end(), 0.); //Calculate total mass 
//	//		cnt = ad_adr; //Reusing cnt to iterate backwards
//	//		
//	//		while (sum_m > max_payload_cap)
//	//		{ // iterate backwards over mass first as do not need to recalculate distance
//	//			sum_m -= cluster_mass_v[cnt];
//	//			temp_num_of_addresses_mass -= 1;
//	//			cnt--;
//	//		}
//	//		//cnt2 = j + ad_adr - 1; // check this indexing
//	//		if (temp_num_of_addresses_mass == 1)
//	//		{
//	//			sum_d = 2. * utility::length(*cl_data[centroid_id][j], opt_route[i]); // check indexing
//	//			rural_drone uav;
//	//			set_up_single_drone(uav, opt_route[i], sum_m);
//	//			drone_v_u.push_back(uav);
//	//		}
//
//	//		else if (temp_num_of_addresses_mass == 0)
//	//		{
//	//			sum_d = 0;
//	//		}
//
//	//		else
//	//		{//If payload capacity for a single drone has been met no need to recalculate distances
//	//			cnt = ad_adr + 2;
//	//			cnt2 = j + ad_adr - 1;
//	//		
//	//			while (sum_d > max_dist)
//	//			{
//	//				sum_d -= total_dist_v[cnt];
//	//				cnt--;
//	//				sum_d -= total_dist_v[cnt];
//	//				cnt--;
//	//				sum_d += utility::length(*cl_data[centroid_id][cnt2], opt_route[i]);
//	//				cnt2--;
//	//				temp_num_of_addresses_distance -= 1;
//
//	//			}
//	//			
//	//			int lowest_num = min(temp_num_of_addresses_distance, temp_num_of_addresses_mass);
//	//			
//	//			for (int k = j; k < lowest_num + j; k++)
//	//			{
//	//				cl_data[i][k]->visited = true;
//
//	//			}
//	//			
//	//			rural_drone uav;
//	//			set_up_single_drone(uav, opt_route[i], sum_m);
//	//			drone_v_u_m.push_back(uav);
//	//			
//	//			all_distances += sum_d;
//	//			all_masses += sum_m;
//	//			number_of_addresses += lowest_num;
//	//			number_of_drones++;
//	//			j += lowest_num;
//	//		}
//
//	//	}
//
//	//}
//	//return std::tuple<int, int, int, int>(all_distances, all_masses, number_of_addresses, number_of_drones);
//}

void rural_drone::set_up_single_drone(rural_drone& uav, address_metadata arg, double mass_sum)
{
	/*this->number_of_drones = number_of_drones;
	for (int i = 0; i < number_of_drones; i++) {
		this->drone_v_u[i] = new rural_drone(this->maximum_battery_time, this->maximum_payload_capacity, this->drone_mass,
			this->payload, this->max_flight_time, this->rotors);*/
	uav.update_payload("Load", mass_sum);
	uav.x_coord = arg.x_coord;
	uav.y_coord = arg.y_coord;
}

void rural_drone::singular_flight(int k, std::vector<std::vector<address_metadata*>>& cl_data, std::vector<address_metadata>& opt_route)
{

	/*for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < cl_data[i].size(); j++)
		{
			rural_drone uav;
			set_up_single_drone(uav, opt_route[i], cl_data[i][k]->parcel_mass);
			drone_v_u.push_back(uav);
		}
	}*/
}



		