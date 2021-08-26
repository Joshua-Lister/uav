#include "rural_drone.h"
//
//rural_drone::rural_drone(double maximum_battery_time, double maximum_payload_capacity, double drone_mass, double payload, double max_flight_time,
//int rotors){}
rural_drone::rural_drone(double maximum_battery_time, double maximum_payload_capacity, double drone_mass, double payload, double max_flight_time,
	int rotors) : drone(maximum_battery_time, maximum_payload_capacity, drone_mass, payload, max_flight_time, rotors){}

rural_drone::rural_drone(double payload, double max_flight_time) : drone(payload, max_flight_time) {};


//bool rural_drone::energy_flight_constraint(double L)
//{
//	/*double energy1 = power_consumption() * (L / horizontal_max_velocity);
//	double dist_to_truck = utility::length(adr, this->x_coord, this->y_coord);*/
//	return true;
//}
//
//std::tuple<int, int, int, int> rural_drone::drone_multi_delivery(int k, int ad_adr, std::vector<std::vector<address_metadata*>>& cl_data, std::vector<address_metadata>& opt_route, double max_payload_cap, double max_dist)
//{
//	int cnt, cnt2, j;
//	int centroid_id;
//	int number_of_drones = 0;
//	int number_of_addresses = 0;
//	int temp_num_of_addresses_distance = 0, temp_num_of_addresses_mass = 0;
//	
//	double sum_d, sum_m;
//	double all_distances = 0, all_masses = 0;
//	
//	std::vector<double> total_dist_v(ad_adr + 2);
//	std::vector<double> cluster_mass_v(ad_adr + 1);
//
//	for (int i = 0; i < k; i++)
//	{ //Iterate over each cluster
//		j = 0;
//
//		centroid_id = opt_route[i].id;
//
//		while (j < cl_data[i].size())
//		{ //Iterate over all addresses with id i
//			
//			int gap_size = cl_data[i].size() - j - 1;
//			
//			if (gap_size < ad_adr + 1)
//			{
//				ad_adr = gap_size - 1;
//			}
//
//			rural_drone* uav;
//
//			cnt = 0;
//			sum_m = 0;
//			sum_d = 0;
//
//			total_dist_v[cnt] = util::length(opt_route[i], *cl_data[centroid_id][j]); //Calculate distance from centroid(id = i) to address with matching id
//			cnt++;
//			for (int adr = j; adr < j + ad_adr; adr++)
//			{ //Iterate over user given part_size (potential maximum number of addresses a single drone can visit)
//				// if cluster only contains one address this doesn't work
//				total_dist_v[cnt] = util::length(*cl_data[centroid_id][adr], *cl_data[centroid_id][adr + 1]); //Calculate distance between addresses
//				cnt++;
//			}
//			
//			total_dist_v[cnt] = util::length(*cl_data[centroid_id][ad_adr + 1 + j], opt_route[i]); //Calculate distance from last address to centroid with matching id
//			
//			cnt = 0; //Assing cnt to 0 to reuse as iterating over parcel mass size now
//			for (int adr = j; adr < j + ad_adr + 1; adr++)
//			{ // ADD IF STATEMENT
//				cluster_mass_v[cnt] = cl_data[centroid_id][adr]->parcel_mass; //Parcel mass of each address
//				cnt++;
//			}
//			
//			temp_num_of_addresses_distance = ad_adr + 1;
//			temp_num_of_addresses_mass = ad_adr + 1;
//			sum_d += std::accumulate(total_dist_v.begin(), total_dist_v.end(), 0.); //Calculate total distance 
//			sum_m += std::accumulate(cluster_mass_v.begin(), cluster_mass_v.end(), 0.); //Calculate total mass 
//			cnt = ad_adr + 1; //Reusing cnt to iterate backwards
//			
//			while (sum_m > max_payload_cap)
//			{ // iterate backwards over mass first as do not need to recalculate distance
//				sum_m -= cluster_mass_v[cnt];
//				temp_num_of_addresses_mass -= 1;
//				cnt--;
//			}
//			//cnt2 = j + ad_adr - 1; // check this indexing
//			if (temp_num_of_addresses_mass == 1)
//			{
//				sum_d = 2. * util::length(*cl_data[centroid_id][j], opt_route[i]); // check indexing
//				uav = new rural_drone(max_payload_cap, max_dist);
//				set_up_single_drone(uav, opt_route[i], sum_m);
//				v1.push_back(uav); 
//			}
//
//			else if (temp_num_of_addresses_mass == 0)
//			{
//				sum_d = 0;
//			}
//
//			else
//			{//If payload capacity for a single drone has been met no need to recalculate distances
//				cnt = ad_adr + 1;
//				cnt2 = j + ad_adr - 1;
//
//				while (sum_d > max_dist)
//				{
//					sum_d -= total_dist_v[cnt];
//					cnt--;
//					sum_d -= total_dist_v[cnt];
//					cnt--;
//					sum_d += util::length(*cl_data[centroid_id][cnt2], opt_route[i]);
//					cnt2--;
//					temp_num_of_addresses_distance -= 1;
//
//				}
//			}
//			int lowest_num = std::min(temp_num_of_addresses_distance, temp_num_of_addresses_mass);
//				
//			for (int k = j; k < lowest_num + j; k++)
//			{
//				cl_data[i][k]->visited = true;
//
//			}
//			uav = new rural_drone(max_payload_cap, max_dist);
//			set_up_single_drone(uav, opt_route[i], sum_m);
//			v2.push_back(uav);
//				
//			all_distances += sum_d;
//			all_masses += sum_m;
//			number_of_addresses += lowest_num;
//			number_of_drones++;
//			j += lowest_num;
//
//		}
//
//	}
//	return std::tuple<int, int, int, int>(all_distances, all_masses, number_of_addresses, number_of_drones);
//}
//std::tuple<int, int, int, int> rural_drone::drone_multi_delivery(int k, int ad_adr, std::vector<std::vector<address_metadata*>>& cl_data, std::vector<address_metadata>& opt_route, double max_payload_cap, double max_dist)
//{
//	int centroid_id;
//	int number_of_drones = 0;
//	int number_of_addresses = 0;
//	int temp_num_of_addresses_distance = 1, temp_num_of_addresses_mass = 1;
//	int j, cnt;
//	double sum_d, sum_m;
//	double all_distances = 0, all_masses = 0;
//	//std::vector<double> distance_track(ad_adr);
//	//std::vector<double> mass_track(ad_adr);
//	//for (int i = 0; i < k; i++)
//	//{ //Iterate over each cluster
//	//	j = 0;
//
//	//	centroid_id = opt_route[i].id;
//
//	//	while (j < cl_data[i].size())
//	//	{
//	//		//int gap_size = cl_data[i].size() - j - 1;
//	//		int gap_size = cl_data[i].size() - j - 1;
//
//	//		if (gap_size < ad_adr + 1) //ad_adr + 1
//	//		{
//	//			ad_adr = gap_size - 1; //- 1;//ad_adr = gap_size - 1;
//	//		}
//
//	//		int num_of_adr = 0;
//	//		sum_d = 0; sum_m = 0;
//	//		cnt = 0;
//	//		sum_d += util::length(opt_route[i], *cl_data[centroid_id][j]);
//	//		double* d2;
//	//		for (int adr = j; adr < j + ad_adr; adr++)
//	//		{ //Iterate over user given part_size (potential maximum number of addresses a single drone can visit)
//	//			// if cluster only contains one address this doesn't work
//	//			double d1 = util::length(*cl_data[centroid_id][adr], *cl_data[centroid_id][adr + 1]);
//	//			*d2 = util::length(*cl_data[centroid_id][adr + 1], opt_route[i]);
//	//			distance_track[cnt] = *d2;
//	//			if (sum_d + d1 + *d2 >= max_dist)
//	//			{
//	//				sum_d += distance_track[cnt];
//	//				sum_m += mass_track[cnt];
//	//				break;
//	//			}
//	//			double m1 = cl_data[centroid_id][adr]->parcel_mass;
//	//			mass_track[cnt] = m1;
//	//			if (sum_m + m1 >= max_payload_cap)
//	//			{
//	//				sum_d += distance_track[cnt];
//	//				sum_m += mass_track[cnt];
//	//				break;
//	//			}
//	//			cnt++;
//	//			sum_d += d1;
//	//			sum_m += m1;
//	//			num_of_adr++;
//
//	//		}
//
//	//		number_of_drones++;
//	//		all_distances += sum_d;
//	//		all_masses += sum_m;
//	//		int lowest_num = std::min(temp_num_of_addresses_distance, temp_num_of_addresses_mass);
//	//		number_of_addresses += lowest_num;
//	//		j += lowest_num;
//	//	}
//	//}
//	std::vector<double> distance_track(ad_adr);
//	std::vector<double> mass_track(ad_adr);
//	for (int i = 0; i < k; i++)
//	{
//		int adr = 0;
//		centroid_id = opt_route[i].id;
//
//		while (adr < cl_data[i].size())
//		{
//			if (cl_data[centroid_id].size() == 1)
//			{
//				sum_d = 2 * util::length(opt_route[i], *cl_data[centroid_id][0]);
//				sum_m = cl_data[centroid_id][0]->parcel_mass;
//				number_of_drones++;
//				all_distances += sum_d;
//				all_masses += sum_m;
//				number_of_addresses++;
//				break;
//			}
//
//			int gap_size = cl_data[i].size() - j - 1;
//			double d1, d2, m1;
//			cnt = 0;
//			sum_d = 0; sum_m = 0;
//			int adr = 0;
//			bool constrained = false;
//
//			sum_d += util::length(opt_route[i], *cl_data[centroid_id][j]);
//			distance_track.push_back(sum_d);
//			//while (!constrained)
//			//{
//			d1 = util::length(*cl_data[centroid_id][adr], *cl_data[centroid_id][adr + 1]);
//			d2 = util::length(*cl_data[centroid_id][adr + 1], opt_route[i]);
//			distance_track.push_back(d2);
//			if (sum_d + d1 + d2 >= max_dist)
//			{
//				sum_d += distance_track[cnt];
//				sum_m += mass_track[cnt];
//				constrained = true;
//				break;
//			}
//			m1 = cl_data[centroid_id][adr]->parcel_mass;
//			mass_track.push_back(m1);
//			if (sum_m + m1 >= max_payload_cap)
//			{
//				sum_d += distance_track[cnt];
//				sum_m += mass_track[cnt];
//				constrained = true;
//				break;
//			}
//	
//			sum_d += d1;
//			sum_m += m1;
//			adr++;
//			cnt++;
//
//			}
//			number_of_drones++;
//			all_distances += sum_d;
//			all_masses += sum_m;
//			int lowest_num = std::min(temp_num_of_addresses_distance, temp_num_of_addresses_mass);
//			number_of_addresses += lowest_num;
//			j += lowest_num;
//		}
//
//	}
//	return std::tuple<int, int, int, int>(all_distances, all_masses, number_of_addresses, number_of_drones);
//}
//}

std::tuple<int, int, int, int> rural_drone::drone_multi_delivery(int k, int ad_adr, std::vector<std::vector<address_metadata*>>& cl_data, std::vector<address_metadata>& opt_route, double max_payload_cap, double max_dist)
{
	int number_of_addresses = 0;
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
		centroid_id = opt_route[i].id;
		cnt_d = 0;
		cnt_m = 1;
		while (j < cl_data[centroid_id].size()) // j < size of cluster 
		{
			if (cl_data[centroid_id].size() == 1) // if cluster size == 1 then can only visit the one address 
			{
				sum_d = 2 * util::length(opt_route[i], *cl_data[centroid_id][0]);
				sum_m = cl_data[centroid_id][0]->parcel_mass;
				cl_data[centroid_id][0]->visited = true;
				number_of_drones++;
				all_distances += sum_d;
				all_masses += sum_m;
				number_of_addresses++;
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
	int e = 1;
	int b = 1;
	return std::tuple<int, int, int, int>(all_distances, all_masses, number_of_addresses, number_of_drones);
}
//void rural_drone::set_up_single_drone(rural_drone* uav, address_metadata arg, double mass_sum)
//{
//	/*this->number_of_drones = number_of_drones;
//	for (int i = 0; i < number_of_drones; i++) {
//		this->drone_v_u[i] = new rural_drone(this->maximum_battery_time, this->maximum_payload_capacity, this->drone_mass,
//			this->payload, this->max_flight_time, this->rotors);*/
//	uav->update_payload("Load", mass_sum);
//	uav->x_coord = arg.x_coord;
//	uav->y_coord = arg.y_coord;
//}

std::tuple<double, int> rural_drone::singular_flight(int k, std::vector<std::vector<address_metadata*>>& cl_data, std::vector<address_metadata>& opt_route)
{
	int centroid_id, num_of_drones;
	int num_of_addresses = 0;
	double all_distances;
	double sum_d = 0;
	double total_parcel_mass = 0;
	for (int i = 0; i < k; i++)
	{
		centroid_id = opt_route[i].id;
		for (int j = 0; j < cl_data[centroid_id].size(); j++)
		{
			sum_d +=  2 * util::length(opt_route[i], *cl_data[centroid_id][j]);
			num_of_addresses++;
			total_parcel_mass += cl_data[centroid_id][j]->parcel_mass;
		}
	}
	return std::tuple<double, int>(sum_d, 1);

}



		